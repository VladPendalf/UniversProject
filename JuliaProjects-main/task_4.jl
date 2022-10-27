include("roblib.jl")
    #=
        invers(side::HorizonSide)
        movements!(r::Robot,side::HorizonSide,num_steps::Int)
        get_num_steps_movements!(r::Robot, side::HorizonSide)
        movements!(r::Robot,side::HorizonSide)
        moves!(r::Robot,side::HorizonSide)
        find_border!(r::Robot,direction_to_border::HorizonSide, direction_of_movement::HorizonSide)
    =#

#= 4) ДАНО: Робот - Робот - в произвольной клетке ограниченного прямоугольного поля
РЕЗУЛЬТАТ: Робот - в исходном положении, и клетки поля промакированы так: нижний ряд - полностью, следующий - весь, за исключением одной последней 
клетки на Востоке, следующий - за исключением двух последних клеток на Востоке, и т.д. =#

function stairs!(r) #Главная функция
    movements!(r,Sud)
    movements!(r,West)
    #Мы в левом нижнем углу

    
    side = Ost
    num_hor = moves!(r,side) #идем вправо и запоминаем длину 1-ой ступени
    movements!(r,West) #возвращаемся в левый угол
    mark_up!(r,num_hor) #идем в доль строки и ставим маркеры, уменьшая с каждой итерацией первоначальную длину строки
end

function mark_up!(r::Robot,size::Int)
    i = 0
    while (1 <= size) #пока длина не равна 0
        for _ in 1:size #движемся на длину строки и ставим маркеры
            move!(r,Ost)
            putmarker!(r)
        end
        if (isborder(r,West) == false) #если , вдруг, маркеры не поставились, поставили опять
            movements!(r,West)
            putmarker!(r)
        end
        if (isborder(r,Nord) == false) #переходим на строчку выше и уменьшаем длину строки
        move!(r,Nord)
        size = size - 1
        else
            break
        end
    end
end