using Core: Matrix
using Base: Integer
#задача 1 Реализовать функцию, аналогичную встроенной функции reverse!, назвав её, например, reverse_user!, для следующих случаев: a) аргумент функции - вектор б) аргумент функции - матрица (2-мерный массив)
function reverse_user!(v::Vector)::Vector
    len = length(v)
    for i in 1:div(len-1, 2, RoundDown) #деление с округлением вниз
        v[i],v[len-i+1] = v[len-i+1],v[i] #меняем элементы с двух сторон
    end
    return v #возвращаем объект типа Vector
end

function reverse_user!(a, dims = 2)::Matrix #не очень понял из документации Julia , какими типами должны быть a и dims ссылка: https://github.com/JuliaLang/julia/blob/6aaedecc447e3d8226d5027fb13d0c3cbfbfea2a/base/arraymath.jl#L93-L100
    l = length(v)
    for i in 1:div(l-1, 2, RoundDown) #деление с округлением вниз
        a[i],a[l-i+1] = a[l-i+1],a[i] #меняем элемент в начаде матрицы и в её конце
    end
    return v
end

#задача 2 Аналогично, реализовать функцию, аналогичную встроенной функции copyдля следующих случаев: a) аргумент функции - вектор б) аргумент функции - матрица (2-мерный массив)
function copy_user!(v::Vector)::Vector
    copy_zero_vect = zero(length(v)) #зануленный вектор длины нашего вектора
    for i in 1:length(v)
        copy_zero_vect[i] = v[i] #копируем значения в новый вектор
    end
    return copy_zero_vect
end

function copy_user!(a, dims = 2)::Matrix
    copy_zero_matrix = zeros(Int, length(a)) #зануленная матрица длиной с нашу исходную матрицу
    for i in 1:length(a)
        copy_zero_matrix[i] = a[i] #копируем значения в новую матрицу
    end
    return copy_zero_matrix
end

#Задача 3 Реализовать алгоритм сортировки методом пузырька, написав следующие 4 обобщенные функции: bubblesort, bubblesort!, bubblesortperm, bubblesortperm!, по аналогии со встоенными функциями sort!, sort, sortperm!, sortperm, ограничившись только случаем, когда входной параметр есть одномерный массив (вектор).
function bubblesort!(v::Vector)::Vector
    len = length(v)
    for i in 1:len-1
        for j in 2:len    
            if v[j-1] > v[j]
                v[j-1],v[j] = v[j],v[j-1]
            end
        end
    end
    return v
end

bubblesort(v::Vector)::Vector = bubblesort!(deepcopy(v)) #возвращает полностью независимый объект

function bubblesortperm!(v::Vector)::Vector
    len = length(a)
    ind = collect(1:len) #массив индексов
    for i in 1:len-1
        fl = false
        
        for j in 1:len-i
            if a[j]>a[j+1]
                a[j],a[j+1] = a[j+1],a[j]
                ind[j],ind[j+1] = ind[j+1],ind[j]
                fl = true
            end
        end
        
        if fl == false
            break
        end
    
    end
    return ind
end

bubblesortperm(v::Vector)::Vector=bubblesortperm!(deepcopy(a))

#Задача 4 На основе разработанных в пункте 1 функций, сотрирующих одномерный массив, написать соответствующие функции, которые бы могли получать на вход матрицу, и сортировать каждый из ее столбцов по отдельности. Имена функций оставить прежними, что были и в пункте 1, воспользовавшись механизмом множественной диспетчеризации языка Julia.
function bubblesort!(A::Matrix)::Matrix
    for i in size(A,2) # идем по числу элементов в матрице
        bubblesort!(@view A[:,i]) #срез на массив 
    end
    return A
end

bubblesort(A::Matrix)=bubblesort!(deepcopy(A))

function bubblesortperm!(A::Matrix)
    ind=Matrix{Int}(undef,size(A)) #создание матрицы типа инт и размером с нашу матрицу
    for i in size(A,2)
        ind[:,i]=bubblesortperm!(@view A[:,i]) 
    end
    return ind
end

bubblesortperm(A::Matrix)=bubblesortperm!(deepcopy(A))

#Задача 5 Написать функцию sortkey!(a, key_values), получающую на вход некоторый вектор a, и соответствующий вектор keyvalues ключевых значений элементов вектора a, осуществляющую сортировку вектора a по ключевым значениям его элементов, и возвращающую ссылку на вектор a. (Для сортировки вектора ключевых значений можно востпользоваться одной из разработанных в пункте 1 функций, или соответствующей встроенной функцией).
function sortkey!(key_values, a)
    ind = sort_bubble_perm!(key_values)
    return @view a[ind]
end

#Задача 7 Написать функции insertsort!, insertsort, insertsortperm, insertsortperm! (по аналогии с пунктом 1) реализующие алгоритм сортировки вставками
function insertsort!(a)
    len = length(a)
    for i in 2:len
        j = i - 1
        while j > 0 && a[j] > a[j+1]
            a[j+1],a[j] = a[j],a[j+1]
            j -= 1
        end 
    end
    return a    
end

insertsort(a) = insertsort!(copy(a))

function insertsortperm!(a)
    len = length(a)
    arr = []
    for i in 1:len
        push!(arr, i)
    end
    for i in 2:len
        j = i - 1
        while j > 0 && a[j] > a[j+1]
            a[j+1], a[j] = a[j], a[j+1]
            arr[j+1],arr[j] = arr[j],arr[j+1]
            j -= 1
        end 
    end
    return arr
end

insertsortperm(a) = insertsortperm!(copy(a))

#Задача 8 Реализовать ранее написанную функцию insertsort! с помощью встроенной функции reduce
insertsort!(A)=reduce(1:length(A))do _, k # в данном случае при выполнении операции вставки  первый аргумент фуктически не используется
    while k>1 && A[k-1] > A[k]
        A[k-1], A[k] = A[k], A[k-1]
        k -= 1
    end
    return A
end