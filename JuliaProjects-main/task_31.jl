#=
    ЗАДАЧА 31. 
    Робот находится где-то внутри лабиринта, граница которого обладает следующим свойством: любая горизонтальная 
    прямая пересекает границу ровно 2 раза (а произвольная вертикальная прямая пересекает ее любое четное число раз).

    Требуется подсчитать число имеющихся на поле маркеров (функция должна это число возвращать) и 
    возвратить Робота в исходное положение.
=#

include("roblib.jl")
    #=
        invers(side::HorizonSide)
        movements!(r::Robot,side::HorizonSide,num_steps::Int)
        get_num_steps_movements!(r::Robot, side::HorizonSide)
        movements!(r::Robot,side::HorizonSide)
        moves!(r::Robot,side::HorizonSide)
        find_border!(r::Robot,direction_to_border::HorizonSide, direction_of_movement::HorizonSide)
    =#

function get_num_markers_lab(robot::Robot)
    # Робот - в произвольной клетке лабиринта

    num_steps, side_steps = move_to_start!(robot, (Sud,West))
    num_steps=reverse(num_steps)
    side_steps=reverse(side_steps)
    # Робот - в юго-западном углу

    side = Ost
    num_markers = get_num_markers!(robot, side)
    # Робот - в "начале" ряда
    while is_move_posible!(robot, Nord, side) == true
        move!(robot, Nord)
        movements!(robot,side)
        side = invers(side)
        num_markers += get_num_markers!(robot, side)
    end
    # Маркеры посчитаны, Робот где-то у северной границы в углу

    move_to_start!(robot, (Sud,West))
    # Робот - снова в юго-западном углу

    for (i,n) in enumerate(num_steps)
        movements!(robot, side_steps[i], n)
    end
    # Робот - в исходном положении
    return num_markers
end

function get_num_markers!(robot, side)  
    nun_markers = ismarker(robot) ? 1 : 0
    while !isborder(robot,side)
        move!(robot,side)
        if ismarker(robot)==true 
            num_markers += 1
    
        end
    end
    return num_markers
end


function is_move_posible!(robot, move_side, find_side)
    while isborder(robot, move_side)
        if !isborder(robot, find_side) 
            move!(robot, find_side)
        else
            return false
        end
    end
    return true
end


function move_to_start(robot, start_side::Tuple)
    num_steps = Int[]
    side_steps = HorizoSide[]
    while !isborder(robot,start_side[2]) || is_posible!(robot, start_side[1], invers(start_side[2]), num_steps, side_steps) 
           for i in 1:2
            push!(num_steps, get_num_movements!(robot,start_side[i]))
            push!(side_steps, start_side[i])
        end
    end
    return num_steps, side_steps
end


function is_move_posible!(robot, move_side, find_side, num_steps::Vector, side_steps::Vector)
    num=0
    while isborder(robot, move_side)
        if !isborder(robot, find_side) 
            num += 1
            move!(robot,find_side)
        else
            push!(num_steps, num)
            push!(side_steps, find_side)
            return false
        end
    end
    push!(num_steps, num)
    push!(side_steps, find_side)

    return true
end