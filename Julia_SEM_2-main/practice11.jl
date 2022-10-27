module Vector2Ds

    export Vector2D, xdot, sin, cos
    using LinearAlgebra # - чтобы стали доступными фунции dot (скалярное произведение), norm (длина вектора)

    Vector2D{T<:Real} = Tuple{T,T}

    Base. cos(a::Vector2D, b::Vector2D) = dot(a,b)/norm(a)/norm(b)
    xdot(a::Vector2D, b::Vector2D) = a[1]*b[2]-a[2]*b[1]
                # xdot(a,b)=|a||b|sin(a,b) - косое произведение
    Base. sin(a::Vector2D, b::Vector2D) = xdot(a,b)/norm(a)/norm(b)
end

using .Vector2Ds

#Задача 1. Написать функцию, возвращающу одномерный массив заданной длины, содержаий случайные точки плоскости типа Vector2D.
randpoints(random::Function, num::Integer) = [(random(),random()) for _ in 1:num]

#Задача 2. Написать функцию, которая получает на вход массив точек плоскости типа Point2D и отображает их на графике.
#На самом деле, писать ничего не потребуется: функция Plots.scatter справляется с этой задачей

#Задача 3. Написать функцию, получающую вектор кортежей, содержащих пары точек типа Vector2D, и возвращающую графический объект (типа Plots.Plot), содержащий изображение соответствующих отрезков, расположенных на плоскости.
function plotsegments(segments::Vector{Tuple{Point2D,Point2D}}; kwargs...)
    p=plot(;kwargs...)
    for s in segments
        plot!(collect(s); kwargs...)
    end
    return p
end