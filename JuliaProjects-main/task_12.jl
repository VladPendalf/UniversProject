#=Задача 12 
На прямоугольном поле произвольных размеров расставить маркеры в виде "шахматных" клеток, начиная с юго-западного угла поля, когда каждая отдельная 
"шахматная" клетка имеет размер n x n клеток поля (n - это параметр функции). Начальное положение Робота - произвольное, конечное - совпадает с 
начальным. Клетки на севере и востоке могут получаться "обрезанными" - зависит от соотношения размеров поля и "шахматных" клеток. 
(Подсказка: здесь могут быть полезными две глобальных переменных, в которых будут содержаться текущие декартовы координаты Робота относительно 
начала координат в левом нижнем углу поля, например)
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


module NNChessMarker
    using HorizonSideRobots
    import Main.inverse

    export mark_chess

    X_COORDINATE=0
    Y_COORDINATE=0

    CELL_SIZE = 0 # - размер "шахматной" клеки

    function mark_chess(r::Robot,n::Int)
        global CELL_SIZE
        CELL_SIZE = n 

        side=Ost
        mark_row(r,side)
        while isborder(r,Nord)==false
            move_decart!(r,Nord)
            side = invers(side)
            mark_row(r,side)
        end
    end

    function mark_row(r::Robot,side::HorizonSide)
        putmarker_chess!(r)
        while isborder(r,side)==false
            move_decart!(r,side)
            putmarker_chess!(r)
        end
    end

    function putmarker_chess!(r)
        if (mod(X_COORDINATE, 2*CELL_SIZE) in 1:CELL_SIZE-1) && (mod(Y_COORDINATE, 2*CELL_SIZE) in 1:CELL_SIZE-1)
            putmarker!(r)
        end
    end

    function move_decart!(r::Robot,side::HorizonSide)
        global X_COORDINATE,Y_COORDINATE
        if side==Nord
            Y_COORDINATE+=1
        elseif side==Sud
            Y_COORDINATE-=1
        elseif side==Ost
            X_COORDINATE+=1
        else
            X_COORDINATE-=1
        end
        move!(r,side)
    end
end