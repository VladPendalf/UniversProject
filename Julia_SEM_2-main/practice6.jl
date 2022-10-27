#Задача 1. Написать функцию, получающую 2 отсортированных массива A и B, и объединяющую их в одном отсортированном массиве C (length(C)=length(A)+length(B)=n). Алгоритм должен иметь оценку сложности O(n). Функцию можно назвать merge. Реализовать 2 варианта этой функции:
function merge(A::Vector{T},B::Vector{T})::Vector{T} where T
    i = 1
    j = 1
    С = Vector{Int}(undef,length(A)+length(B))
    for it1 in 1:length(A)
        C[it1+it2-1] = A[it1]
        if (A[it1] < B[it2]) && (it2 < length(B)) #
            C[it1+it2-1] = B[it2]
            it2+=1
        end
    end
    return C
end

#Задача 2 Написать функцию, выполняющую частичную сортировку. А именно, функция получает некоторый массив A и некоторое значение b, и переставляет элементы в массивае A так, что бы в нём сначала шли все элементы, меньшие b, затем - все, равные b, и затем, наконец, - все большие b. Алгоритм должен иметь оценку сложности O(n). Реализовать следующие 2 варианта этой функции:
#a) c использованием 3-х вспомогательных массивов (с последующим их объединением в один)
function sort_b_arr(V::Vector{T},b::Int64)::Vector{T} where T
    V1 = Vector{Int}(undef,0)
    V2 = Vector{Int}(undef,0)
    V3 = Vector{Int}(undef,0)
    for i in V
        if (i < b)
            push!(V1,i)
        elseif (i == b)
            push!(V2,i)
        elseif (i > b)
            push!(V3,i)
        end
    end
    return append!(append!(V1,V2),V3)
end

#Задача 3 Написать функцию, выполняющую частичную сортировку. А именно, функция получает некоторый массив A и некотрое значение b, и переставляет элементы в массивае A так, чтобы в нём сначала шли все элементы, меньшие или равные b, а затем - все большие b. Алгоритм должен иметь оценку сложности O(n).
function sort_(A::Vector{T},b::Int64)::Vector{T} where T
    V1 = Vector{Int}(undef,0)
    V2 = Vector{Int}(undef,0)
    for i in A
        if (i<=b)
            push!(V1,i)
        else
            push!(V2,i)
        end
    end
    return append!(V1,V2)
end

