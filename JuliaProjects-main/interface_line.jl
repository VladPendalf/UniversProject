using HorizonSideRobots

"""
interface_line(move!::Function)

    Получает "защищённую" функцию move!(side)::Bool, выполняющую перемещение Робота в ближайшую доступную клетку в направлении side и 
    возвращающую true, 
    если доступная клетка существует, и оставляющую Робота на месте и возвращающую false - в противном случае

возвращает кортеж функций:

    movements!(side) - перемещает Робота "до упора" в заданном направлении
    movements!(side, num_steps::Integer) - перемещает Робота в заданном направлении на заданное число шагов
    movements!(action!::Function, side) - перемещает Робота "до упора" в заданном направлении
    movements!(action!::Function, side, num_steps::Integer) - перемещает Робота в заданном направлении на заданное число шагов

    get_num_movements!(side) - перемещает Робота "до упора" в заданном направлении и возвращает число сделанных шагов
    get_num_movements!(action!::Function, side) - перемещает Робота "до упора" в заданном направлении и возвращает число сделанных шагов

    при этом в соответствующих случаях здесь после каждого шага выполняется action!()

"""
interface_line(move!::Function) = begin
    movements!(side) = while move!(side)==true end
    movements!(side, num_steps::Integer) = for _ in 1:num_steps move!(side) end
    movements!(action::Function, side) = while move!(side)==true action() end
    movements!(action!::Function, side, num_steps::Integer) = for _ in 1:num_steps move!(side); action!() end

    function get_num_movements!(side)
        num_steps=0
        while move!(side)==true
            num_steps+=1
        end
        return num_steps
    end

    function get_num_movements!(action::Function, side)
        num_steps=0
        while move!(side)==true
            action()
            num_steps+=1
        end
        return num_steps
    end

    return (;movements!, get_num_movements!)
end # interface_line-----------------------------------------------