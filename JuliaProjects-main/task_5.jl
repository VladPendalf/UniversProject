include("roblib.jl")
    #=
        invers(side::HorizonSide)
        movements!(r::Robot,side::HorizonSide,num_steps::Int)
        get_num_steps_movements!(r::Robot, side::HorizonSide)
        movements!(r::Robot,side::HorizonSide)
        moves!(r::Robot,side::HorizonSide)
        find_border!(r::Robot,direction_to_border::HorizonSide, direction_of_movement::HorizonSide)
    =#


    #= 5) ДАНО: Робот - в произвольной клетке ограниченного прямоугольного поля, на котором могут находиться также внутренние прямоугольные 
перегородки (все перегородки изолированы друг от друга, прямоугольники могут вырождаться в отрезки)
РЕЗУЛЬТАТ: Робот - в исходном положении и в углах поля стоят маркеры =#

function mark_angles(r)
    num_steps=[]
    while isborder(r,Sud)==false || isborder(r,West) == false # Робот - не в юго-западном углу
        push!(num_steps, moves!(r, West))
        push!(num_steps, moves!(r, Sud))
    end
    #Робот - в юго-западном углу и в num_steps - закодирован пройденный путь
    for side in (Nord,Ost,Sud,West)
        movements!(r,side)
        putmarker!(r)
    end
    # Маркеры поставлены и Робот - в юго-западном углу

    for (i,n) in enumerate(num_steps) # enumerate() - дает не только значение элемента, но и число итераций на данный момент
        side = isodd(i) ? Ost : Nord # isodd() == true -> если число нечетное , isodd() == false -> если четное
        movements!(r,side,n)
    end
    # Робот - в исходном положении
end