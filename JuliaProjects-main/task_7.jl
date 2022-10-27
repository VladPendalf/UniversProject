include("roblib.jl") 
#=
    invers(side::HorizonSide) инверсия
    movements!(r::Robot,side::HorizonSide,num_steps::Int) {возвращение на num_steps шагов}
    get_num_steps_movements!(r::Robot, side::HorizonSide) запоминаем кол-во шагов в направлении side
    movements!(r::Robot,side::HorizonSide) идем в направлении side до стенки
    moves!(r::Robot,side::HorizonSide) идем в направлении side до стенки и запоминаем шаги
    find_border!(r::Robot,direction_to_border::HorizonSide, direction_of_movement::HorizonSide) Дойти до стороны, двигаясь змейкой вверх-вниз и вернуть последнее перед остановкой направление
=#

#= Задача 7
ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля (без внутренних перегородок)

РЕЗУЛЬТАТ: Робот - в исходном положении, в клетке с роботом стоит маркер, и все остальные клетки поля промаркированы в шахматном порядке =#

#= Это мой план кода. 
ф-ия ...
    ставим маркер
    делаем два шага вниз
    ставим маркер
    если внизу преграда через 1 ставим в side маркеры
    делаем шаг на вверх + в side
    ставим маркеры через 1
=#

 #Моя первая реализация - и она работает, но при помощи модуля решение смотрится более красиво
 #= function chess!(r::Robot)
    num_hor = moves!(r,West)
    num_vert = moves!(r,Sud)
   #Левый нижний угол

   side = Ost
   if ((num_hor % 2) == 0) #если слево расстояние четна
       if ((num_vert % 2) == 0) # если вертикаль четна
           putmarks2!(r,side)
       else # если вертикаль не четна
           putmarks1!(r,side)
       end
   else
       putmarks1!(r,side)
   end
   #алгоритм - выполнен

   movements!(r,West)
   movements!(r,Sud)

   movements!(r,Ost,num_hor)
   movements!(r,Nord,num_vert)
end

function putmarks1!(r::Robot,side::HorizonSide)
   movements!(r,invers(side))
   move!(r,side)
   while isborder(r,side) == false        
       putmarker!(r)
       for _ in 1:2
           if (isborder(r,side) == false)
               move!(r,side)
           else
               if (isborder(r,Nord) == fasle)
                   move!(r,Nord)
                   side = invers(side)
                   move!(r,side)
               end
           end
       end
   end
   putmarker!(r)
   if (isborder(r,Nord) == false)
       move!(r,Nord)
       putmarks2!(r,Ost)
   end
end


function putmarks2!(r::Robot,side::HorizonSide)
   movements!(r,invers(side))
   while isborder(r,side) == false
       putmarker!(r)
       for _ in 1:2
           if (isborder(r, side) == false)
               move!(r,side)
           else
               if (isborder(r,Nord) == false)
                   move!(r,Nord)
                   side = invers(side)
               end
           end
       end
   end
end

invers(side::HorizonSide) = HorizonSide(mod(Int(side) + 2,4)) =#

# Первое знакомство с модулями. Аналогия из C++ -> namespace
module ChessMark
    using HorizonSideRobots
    import Main.moves!, Main.invers ,Main.get_num_steps_movements!,Main.putmarker,Main.movements!

    export mark_chess

    FLAG_MARK = nothing

    function mark_chess(r)
        global FLAG_MARK

        num_hor =  get_num_steps_movements!(r,West)
        num_vert = get_num_steps_movements!(r,Sud)
        #Робот в ЮГО-ЗАПАДНОМ углу

        FLAG_MARK = isodd(num_hor+num_vert) ? true : false

        side = Ost
        mark_chess(r,side)
        while isborder(r,Nord)==false
            move!(r,Nord); FLAG_MARK = !FLAG_MARK
            side = invers(side)
            mark_chess(r,side)
        end
        #Робот - у северной границы поля И маркеры расставлены в шахматном порядке

        for side in (West,Sud) moves!(r,side) end
        #Робот в юго-западном углу

        movements!(r,Ost,num_hor)
        movements!(r,Nord,num_vert)
    end

    function mark_chess(r::Robot,side::HorizonSide)
        global FLAG_MARK
        while isborder(r,side)==false
            if FLAG_MARK == true
                putmarker(r)
            end
            move!(r,side); FLAG_MARK = !FLAG_MARK
        end
    end
end
