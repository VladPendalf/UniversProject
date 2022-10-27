include("roblib.jl") 
#=
    invers(side::HorizonSide) инверсия
    movements!(r::Robot,side::HorizonSide,num_steps::Int) {возвращение на num_steps шагов}
    get_num_steps_movements!(r::Robot, side::HorizonSide) запоминаем кол-во шагов в направлении side
    movements!(r::Robot,side::HorizonSide) идем в направлении side до стенки
    moves!(r::Robot,side::HorizonSide) идем в направлении side до стенки и запоминаем шаги
    find_border!(r::Robot,direction_to_border::HorizonSide, direction_of_movement::HorizonSide) Дойти до стороны, двигаясь змейкой вверх-вниз и вернуть последнее перед остановкой направление
=#
#=
Задачa 13: 
ДАНО: Робот - в произвольной клетке ограниченного прямоугольной рамкой поля без внутренних перегородок и маркеров.

РЕЗУЛЬТАТ: Робот - в исходном положении в центре косого креста (в форме X) из маркеров.
=#

function mark_kross_x(r::Robot)
    for side in ((Nord,Ost),(Sud,Ost),(Sud,West),(Nord,West))
        while (isborder(r,side[1])==false && isborder(r,side[2])==false)
            move!(r,side[1])
            move!(r,side[2])
            putmarker!(r)
        end
        while (ismarker(r)==true)
            move!(r, invers(side[1]))
            move!(r, invers(side[2]))
        end
    end
    putmarker!(r)
end