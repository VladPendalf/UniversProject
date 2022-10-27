#= ДАНО: Робот находится в произвольной клетке ограниченного прямоугольного поля без внутренних перегородок и маркеров.

 РЕЗУЛЬТАТ: Робот — в исходном положении в центре прямого креста из маркеров, расставленных вплоть до внешней рамки.
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


 function mark_kross!(r::Robot)     #Основная функция 
    for side in (Nord,West,Sud,Ost) #Идем во все стороны
        num_steps=get_num_steps_putmarkers!(r,side) #запомнимаем число шагов
        movements!(r,invers(side),num_steps) #Возвращаемся
    end
    putmarker!(r) #Ставим маркеры
end

invers(side::HorizonSide) = HorizonSide(mod(Int(side) + 2,4)) #Меняем направление на противоположное 

function get_num_steps_putmarkers!(r::Robot,side::HorizonSide) #Идем в side и запоминаем шаги
    num_steps=0
    while isborder(r, side) == false #пока нет стенки
        move!(r,side)
        putmarker!(r)
        num_steps += 1 
    end
    return num_steps #Возвращаем число шагов
end

movements!(r::Robot,side::HorizonSide,num_steps::Int) = #движение
    for _ in 1:num_steps
        move!(r,side)
    end