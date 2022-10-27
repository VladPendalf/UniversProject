using HorizonSideRobots

"""
interface_trajectories(robot)

-- robot - именованный кортеж, содержащий интерфейс Робота, включающий функции
    move!, isborder
-- Возвращает интерфейс, содержащий функции:

snake!(move_fold!::Function, fold_direct::HorizonSide, general_direct::HorizonSide)

    Осуществляет проход Робота по рядам "змейкой" (в местах разворота возможны самоналожения траектории, и последняя складка может получиться полностью наложена на предыдущую)
    -- move_fold!(::HorizonSide) - функция, перемещающая Робота по очередной "складке змейки", и возвращающая логическое значение:
    если возвращает false, то  - это сигнал, чтобы движение "змейкой" было остановлено
    -- fold_direct - направление перемещения по (самой первой) "складке" 
    -- general_direct - направление перемещения от "складки" к "складке"

labirint_snake!(move_fold!::Function, fold_direct::HorizonSide, general_direct::HorizonSide)

    Осуществляет проход Робота по рядам простого лабиринта "змейкой". 
    Под простым лабиринтом понимается лабиринт который пересекается горизонтальными пярмыми ровно два раза. 
    При этом в местах разворота возможны самоналожения траектории (последняя складка будет получиться полностью наложеннной на предыдущую),
    но функция move_fold! отвечает только за одноразовый проход по складке (самоналожения могут возникать только при попытках перемещения на новую склажку).
    -- move_fold!(::HorizonSide) - функция, перемещающая Робота по очередной "складке змейки", и, ВОЗМОЖНО, возвращающая логическое значение:
    если возвращает false, то  - это сигнал, чтобы движение "змейкой" было остановлено 
    (в принципе, move_fold!(...) может возвращать и любое другое значение, не обязательно типа Bool, например - nothing, 
    но тогда "змейка" будет пройдена до самого конца)
    -- fold_direct - направление перемещения по (самой первой) "складке" 
    -- general_direct - направление перемещения от "складки" к "складке"

comb!(there_and_back!::Function, clove_direct::HorizonSide, general_direct::HorizonSide)

    -- Осуществляет проход Роботом по рядам "гребенкой"
    -- there_and_back!(::HorizonSide) - функция, перемещающая Робота по очередному "зубчику гребёнки", от его начала до конца и обрантно, и 
    возвращающая логическое значение: если возвращает false, то  - это сигнал, чтобы движение "гребенкой" было остановлено
    -- clove_direct - направления, определяющие направление перемещения по самому первому "зубчику"
    -- general_direct - направление перемещения от "зубчика" к "зубчику"

spiral!(move_act!::Function)

    Перемещает Робота по раскручивающейся в положительном направлении спирали (первый шаг - на север) до момента наступления 
    некотрого события, определяемого функцией move_act!(::HorizonSide)
    -- move_act!(::HorizonSide)::Bool - функция перемещающая Робота в заданном направлении на 1 шаг (и, возможно, делающая что-то еще), и
    возвращая логическое значение: если возвращается false, то - это сигнал, чтобы движение "змейкой" было остановлено.
"""
include("roblib.jl") 
#=
    invers(side::HorizonSide) инверсия
    movements!(r::Robot,side::HorizonSide,num_steps::Int) {возвращение на num_steps шагов}
    get_num_steps_movements!(r::Robot, side::HorizonSide) запоминаем кол-во шагов в направлении side
    movements!(r::Robot,side::HorizonSide) идем в направлении side до стенки
    moves!(r::Robot,side::HorizonSide) идем в направлении side до стенки и запоминаем шаги
    find_border!(r::Robot,direction_to_border::HorizonSide, direction_of_movement::HorizonSide) Дойти до стороны, двигаясь змейкой вверх-вниз и вернуть последнее перед остановкой направление
=#

function interface_trajectories(robot)

  function snake!(move_fold!::Function, fold_direct::HorizonSide, general_direct::HorizonSide)
    if move_fold!(fold_direct)==false
      return
    end
    while !robot.isborder(general_direct)
      robot.move!(general_direct)
      fold_direct = invers(fold_direct)
      if move_fold!(fold_direct)==false
        return
      end
    end
  end # function snake!

  function labirint_snake!(move_fold!::Function, fold_direct::HorizonSide, general_direct::HorizonSide)

    function to_next_fold!(general_direct)::Bool 
      # перемещающает Робота в начало следующей "складки", если это возможно
      prew_direct = fold_direct
      fold_direct = invers(fold_direct) # - внешняя переменная
      while robot.isborder(general_direct)
        if !robot.isborder(fold_direct)
          robot.move!(fold_direct)
        else
          return false # прохода в направлении general_direct нигде нет
        end
      end
      #УТВ: в направлении general_direct нет перегородки
      robot.move!(general_direct) #!!!
      while !robot.isborder(prew_direct)
        robot.move!(prew_direct)
      end
      return true
    end # nested function to_next_fold!

    if move_fold!(fold_direct)==false
      return
    end
    while to_next_fold!(general_direct)==true
      if move_fold!(fold_direct)==false
        return
      end
    end
  end # function labirint_snake!

  function spiral!(move_act!::Function)

    function next_round!(side, max_num_steps::Integer) # - на очереном витке увеличивает длину сегмента спирали
      if side in (Sud, Nord)
        max_num_steps+=1
      end
      return max_num_steps
    end # nested function next_round!

    function move_direct!(move_act!::Function, side, max_num_steps::Integer)
    # перемещает Робота в заданном направлении не более чем на max_num_steps шагов с помощью функции move_act!(side)
      num_steps=0
      while (num_steps <= max_num_steps)
        if move_act!(side) == false
          return false
        end
        num_steps+=1
      end
      return true
    end # nested function move_direct!

    side = Nord
    max_num_steps = 1
    while move_direct!(move_act!, side, max_num_steps) == true
      max_num_steps = next_round!(side, max_num_steps)
      side=left(side)
    end
  end # function spiral!

  function comb!(there_and_back!::Function, clove_direct::HorizonSide, general_direct::HorizonSide)

    function to_next_clove!(general_direct)
      if !robot.isborder(general_direct)
        robot.move!(general_direct)
        return true
      else
        return false
      end
    end # nested function to_next_clove

    there_and_back!(clove_direct)
    while to_next_clove!(general_direct) && there_and_back!(clove_direct)
    end
  end # function comb!

  return (;snake!, labirint_snake!, comb!, spiral!)
end # function interface_trajectories----------------------------------