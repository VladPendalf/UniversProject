#Задача 15
#= ДАНО: Робот - в произвольной клетке поля 

РЕЗУЛЬТАТ: Робот - в исходном положении, и все клетки по периметру внешней рамки промакированы
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

STEP = 0

function mark_frame_perimetr!(r::Robot)
    num_steps=[]
    while isborder(r,Sud)==false || isborder(r,West) == false # Робот - не в юго-западном углу
        push!(num_steps, moves!(r, West))
        push!(num_steps, moves!(r, Sud))
    end
    
    for side in (Nord,Ost,Sud,West)
        putmarkers!(r, side) 
    end 
    #УТВ: По всему периметру стоят маркеры
    
    for (i,n) in enumerate(num_steps)
        side = isodd(i) ? Ost : Nord # odd - нечетный
        movements!(r,side,n)
    end
    #УТВ: Робот - в исходном положении
end
    
    function moves!(r::Robot,side::HorizonSide)
        num_steps=0
        while isborder(r,side)==false
            move!(r,side)
            num_steps+=1
        end
        return num_steps
    end
    
    function moves!(r::Robot,side::HorizonSide,num_steps::Int)
        for _ in 1:num_steps # символ "_" заменяет фактически не используемую переменную
            move!(r,side)
        end
    end
    
    function putmarkers!(r::Robot, side::HorizonSide)
        putmarker!(r)
        while isborder(r,side)==false
            move!(r,side)
            putmarker!(r)
        end
    end