#Задача 1. Реализовать метод Ньютона, написав функцию со следующим заголовком
function newton(r::Function, x; ε_x = 1e-8, ε_y = 1e-8, nmaxiter = 20)
    x_k = x
    i = 0
    while (i <= nmaxiter && (abs(x_k-x) > ε_x || x_k == x))
        x = x_k
        x_k = x - r(x)
        i+=1
    end
    if (i > nmaxiter)
        return nothing
    else
        return x_k
    end
end

#Задача 2. Решить с помощью этой функции (newton) уравнение $\cos(x)=x$.
newton(x->(x-cos(x))/(1+sin(x)), 0.5)

#Задача 3. Реализовать ещё один метод функции newton со следующим заголовком
newton(ff::Tuple{Function,Function}, x; ε_x=1e-8, ε_y=1e-8, nmaxiter=20) = newton(x->ff[1](x)/ff[2](x), x; ε_x, ε_y, nmaxiter)

#Задача 4. Решить с помощью этого варианта функции newton уравнение $\cos(x)=x$.
newton((x->x-cos(x), x->1+sin(x)), 0.5) 

#Задача 5. Реализовать еще один метод функции newton со следующим заголовком
newton(ff, x; ε_x=1e-8, ε_y=1e-8, nmaxiter=20) = newton(x->(y=ff(x); y[1]/y[2]), x; ε_x, ε_y, nmaxiter)

#Задача 6. Решить с помощью последнего варианта функции newton уравнение $\cos(x)=x$.
newton(x->(x-cos(x),1+sin(x)), 0.5) 

#Задача 7. Реализовать еще один метод функции newton со следующим заголовком
newton(polinom_coeff::Vector{Number}, x; ε_x=1e-8, ε_y=1e-8, nmaxiter=20) = newton(x->(y=evaldiffpoly(x, polynom_coeff); y[1]/y[2]), x; ε_x, ε_y, nmaxiter)

function evaldiffpoly(x,polynom_coeff)
    Q′=0
    Q=0
    for a in polinom_coeff
        Q′=Q′x+Q
        Q=Q*x+a
    end
    return Q, Q′
end