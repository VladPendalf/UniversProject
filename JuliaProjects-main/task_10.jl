#=Задача 10 
ДАНО: Робот - в юго-западном углу поля, на котором расставлено некоторое количество маркеров
РЕЗУЛЬТАТ: Функция верула значение средней температуры всех замаркированных клеток
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

    #простите, но я не смог вывести значение. Он возвращает NaN (т.е. либо деление на 0, либо бесконечность на бесконечность)

function sigma_temper!(r::Robot)::Real
    side = Ost
    count = 0
    total = 0
    res = 0
    total = search_temp(r,side,res,count)
    return total
end

function search_temp(r::Robot,side::HorizonSide, count::Int, res::Int)::Real
    while (isborder(r,side)==false)#идем до упора
        if (ismarker(r) == true)#если в клетке маркер, то считываем температуру
            res += temperature(r)
            count += 1
        end
        move!(r,side)
    end #дошли до конца первой линии
    if (isborder(r,Nord)==false)#если сверху нет преграды
        move!(r,Nord)#делаем шаг
        if (ismarker(r) == true)#если в клетке маркер, то считываем температуру
            res += temperature(r)
            count += 1
        end
        side = invers(side)#меняем направление на противоположное
        search_temp(r,side,count,res)#повторяем алгоритм
    end
    return (res/ count)
end