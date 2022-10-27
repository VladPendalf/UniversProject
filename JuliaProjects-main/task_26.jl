#Задача 26
include("roblib.jl")
"""
    mark_zebra!(r, line_side, ortogonal_line_side, num_passes, num_start_passes)

Расставляет параллельные полосы из маркеров с заданным промежутком между ними и с задаеным промежутком между стартовым углом и первой полосой, и возвращает робота в исходное положение

-- r - cсылка на Робота
-- line_side - начальное направление вдоль полосы маркеров (оно должно инвертироваться от полосы к полосы) 
-- ortogonal_line_side - направление поперек полос с маркерами
-- num_passes - число пустых полос в промежутке между полосами с маркерами
-- num_start_passes - число пустых полос в промежутке между стартовым углом и первой полосой с маркерами

При этом стартовый угол определяется значениями line_side, ortogonal_line_side
"""
function mark_zebra!(robot::Robot, line_side, ortogonal_line_side, num_passes, num_start_passes=0)
    start_side = get_start_side(line_side,ortogonal_line_side)
    #УТВ: start_side - кортеж типа NTuple{2,HorizonSide}, например: (Sud,Ost)  

    num_steps = [get_num_steps_movements!(robot,start_side[i]) for i in 1:2]
    #УТВ: Робот - в стартовом углу

    movements_if_posible!(robot, ortogonal_line_side, num_start_passes) || return
    line_mark!(robot,line_side)
    #ИНВАРИАНТ: линия с Роботом и все предыдущие (по ходу движения в направлении ortogonal_line_side) замаркированы
    while movements_if_posible!(robot,ortogonal_line_side, num_passes) == true
        line_side = invers(line_side)
        line_mark!(robot,line_side)
    end
    #УТВ: все линии замаркированы

    for s in start_side
        movements!(r,s)
    end
    #УТВ: Робот - снова в стартовом углу

    back_side=invers(start_side)
    for (i,num) in enumerate(num_steps)
        side = isodd(i) ? invers(line_side) : invers(ortogonal_line_side)
        movements!(robot,side, num)
    end
    #УТВ: Робот - в исходном положении
end

function movements_if_posible!(robot, side, max_num_steps)
    for _ in 1:max_num_steps
        isborder(robot,side) && (return false)
        move!(robot,side)
    end
    return true
end

function line_mark!(robot,side)
    putmarker!(robot)
    putmarkers!(robot,side)
end

get_start_side(line_side::HorizonSide,ortogonal_line_side::HorizonSide) = (line_side,ortogonal_line_side)


get_start_side(line_side::NTuple{2,HorizonSide}, ortogonal_line_side::NTuple{2,HorizonSide}) = ortogonal_line_side
# первый аргумент здесь фактически не используется
HorizonSideRobots.isborder(r::Robot,side::NTuple{2,HorizonSide}) = isborder(r,side[1]) || isborder(r,side[2])

HorizonSideRobots.move!(r::Robot,side::NTuple{2,HorizonSide}) = for s in side move!(r,s) end

putmarkers!(r::Robot,side::NTuple{2,HorizonSide}) =
    while isborder(r,side)==false
        move!(r,side)
        putmatker!(r)
    end