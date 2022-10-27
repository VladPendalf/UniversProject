using Core: Matrix
#Задача 1 Написать функцию, вычисляющую n-ую частичную сумму ряда Тейлора функции cos(x)=1-...
function T1(n,x)
    sum = 1
    fact = 1
    for i in 1:n
        fact *= i
        if (i%2 == 0)
            sum += (((-1)^((i/2) % 2)) * (x^i))/fact
        end
    end
    return sum
end

#Задача 2 Написать функцию, вычисляющую значение суммы ряда Тейлора функции cos(x) в заданной точке с машинной точностью.
function T2(x,ε)
    sum,fact = 1,1
    i,a = 1,1
    while (abs(a) > ε)
        fact *= i
        if (i%2 == 0)
            a = (((-1)^((i/2)%2))*(x^i))/fact
            sum += a
        end
        i += 1
    end
    return sum
end

#Задача 5. Следующий степенной ряд определяет семейство так называемых функций Бесселя 1-го рода порядка $m$ ($m=0,1,2,...$) $$ J_m(x)=\Big(\frac{x}{2}\Big)^m\sum_{k=0}^{\infty}\frac{(-1)^k}{k!(k+m)!}\Big(\frac{x}{2}\Big)^{2k} $$ Написать функцию besselj(m,x), вычисляющую функцию Бесселя 1-го рода порядка $m$ в точке $x \in \mathbb{R}$ с машинной точностью, и построить семейство графиков для $m=0,1,2,3,4,5$
function bessel(m,x)
    sum = 1/factorial(m)
    i,a = 1,1
    while (abs(a) > ε)
        a *= ((-1)/(i*(i+m)))*(x/2)*(x/2)
        sum += a
        i += 1
    end
    sum *= (x/2)^m
    return sum
end

#Задача 6 Написать функцию linsolve(A,b), получающую на вход невырожденную квадратную верхнетреугольную матрицу A (матрицу СЛАУ, приведенную к ступенчатому виду), вектор-столбец b (правую часть СЛАУ), и возвращающую решение соответствующей СЛАУ.

function linsolve(A::AbstractMatrix,b::AbstractVector)
    x=similar(b)
    for k in reverse(eachindex) # lastindex(x):-1:firstindex(x)
        x[k] = (b[k]-sum((@view A[k,k+1:lastindex(A,2)]).*(@view x[k+1:lastindex(x)])))
    end
    return x
end

#Задача 7. Написать функцию convert!(A), получающую на вход прямоугольную матрицу (например, - расширенную матрицу СЛАУ) и пробразующую эту матрицу к ступенчатому виду с помощью элементарных преобразований строк.
function convert!(A)
    for k in firstindex(A,1):lastindex(A,1)
        imax = argmax(abs, @view A[k:end,k])
        # предполагается, что A[imax, k] != 0
        colon_to_zeros!(A,k,imax)
end

function colon_to_zeros(A,k,imax)
    if imax != k
        A[k,:], A[imax,:] = A[imax,:], A[k,:] 
    end
    for i in k+1:lastindex(A,1)
        if isappoxzero(A[i,k]) 
            continue
        end
        t=-A[i,k]/A[k,k]
        A[i,i:end] += t*(@view A[k,i:end])  
    end
end

function argmax(f::Function, a::AbstractVector)
    imax = firstindex(a)
    for i in firstindex(a)+1:lastindex(a)
        if f(a[i])>f(a[imax])
            imax = i
        end
    end
    return imax
end

isapproxzero(a::Float64)=isapprox(a,0.0; atol=1e-8)

#Задача 8. Написать функцию det(A), получающую на вход квадратную матрицу, и возвращающую значение её определителя.
function issingular_convert!(A)
    for k in firstindex(A,1):lastindex(A,1)
        imax = argmax(mod, @view A[k:end,k])       
        if isappoxzero(A[i,k])
            return nothing
        end
        colon_to_zeros!(A,k,imax)
    end
end

#Задача 10 Написать функцию rang(A), получающую на вход матрицу (вообще говоря, прямоугольную), и возвращающую её ранг.
function det(A) #вычисляем определитель
    B=copy(A)
    if issingular_convert!(B)==true
        return 0
    else
        det=B[1][1]
        for i in 2:length(B)
            det*=B[i][i]
        end
        return det
    end
end

function rang(A::Matrix)
    B = copy(A)
    rang = length(B)
    while (det(B) == 0 && rang != 1)
        rang -= 1
        B = B[1:rang]
    end
    return rang
end