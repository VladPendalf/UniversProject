using Core: Matrix
#Задача 1. Написать функцию с заголовком findallmax(A::AbstractVector)::AbstractVector{Int}, возвращающую вектор индексов всех элементов массива A, имеющих максимальное значение. Алгоритм должен быть однопроходным, т.е. иметь асимптотическую оценку вычислительной сложности O(n).
function findallmax(a::AbstractVector)::AbstractVector{Int}
    i_max=Vector{Int}(undef,size(a))
    i_max[begin]=firstindex(a)
    n = firstindex(i_max)
    for i in firstindex(a)+1:lastindex(a)
        if A[i]>A[i_max[end]]
            i_max[begin]=i
            n = firstindex(i_max)
        elseif A[i]==A[i_max[end]]
            n+=1
            i_max[n]=i
        end
    end
    return resize!(i_max,n)
end

#Задача 2.  Во-первых, можно запоминать индекс последнего элемента с левого конца массива, на котором закнчиватся гарантированный правильный порядок следования элементов массимва, с тем, чтобы на следующей итерации можно было бы начитнать сразу с этой позиции.
function bubble_sort_improving_part_1(v::Vector)::Vector #сортировка с сохранением индекса
    len=length(v)
    ind = 1
    for i in ind:len-1
        for j in ind + 1:len
            
            if v[j-1] > v[j]
                v[j-1],v[j] = v[j],v[j-1]
            end
        
        end
        ind += 1
    end
    return v
end

#Задача 3. Во-вторых, пузырьковую сортировку можно сделать, так сказать, двунаправленной, т.е. сначала очередной наибольший элемент премещать до своего окончательного положения влево, а затем, начиная с предыдущего ему элемента перемещать очередной наименьший элемент до конца влево. Такой способ сортировки принято называть еще "шенкерной" сортрирвкой. Наглядно это показано, например, здесь
function bubble_sort_improving_part_2(v::Vector)::Vector #сортировка в 2 стороны
    left=firstindex(v) #обозначили 2 границы их индексами
    right=lastindex(v)
    while (left < right)
        for i in right:-1:left+1
            if (v[i-1] > v[i])
                v[i-1],v[i] = v[i],v[i-1]
            end
        end
        left =+ 1
        for i in left+1:right
            if (v[i-1] > v[i])
                v[i-1],v[i] = v[i],v[i-1]
            end
        end
        right -= 1
    end
    return(v)
end

#Задача 5 Написать функцию с заголовком возвращающую соответствующий срез неокоторого одномерного массива A.
function slice(A::Vector{T},p::Vector{Int})::Vector{T} where T
    return A[p]
end

#Задача 6 Пусть perm - это некоторый вектор перестановок индексов одномерного массива A. Написать свою реализацию встроенной функции permute!(A, perm), реализующую соответствующее премещение элементов массива A на месте (in-plice), т.е. без копирования их в новый массив . (Cвой вариант этой функции можно назвать permute_!).

function permute_!(A::Vector{T},perm::Vector{Int})::Vector{T} where T
    temp = 0
    for i in perm
        if perm[i] != i
            temp = A[perm[i]]
            A[perm[i]] = A[i]
        end
    end
    return A
end

#Задача 7 Реализовать встроенные функции вставки/добавления (deleteat!, insert!) элемента массива
function deleteat!(V::Vector{T},at::Int)::Vector{T} where T
    answ_vector = Vector{Int}(undef,length(V)-1)
    i = 1
    j = 1
    while (i < length(V))
        if j != at
            answ_vector[i] = V[j]
            i += 1
        end
        j += 1
    end
    return answ_vector
end

function insertat!(V::Vector{T},at::Int,value::T)::Vector{T} where T
    answ_vector = Vector{Int}(undef,length(V)-1)
    i = 1
    j = 1
    while (at <= length(answ_vector))
        if j == at
            answ_vector[i] = value
            j -= 1
            at =- 1
        else
            answ_vector[i] = A[j]
        end
        j += 1
        i += 1
    end
    return answ_vector
end

#Задача 9. Реализовать встроенную функцию reverse!, переставляющую элементы в обратном порядке в самом массиве, т.е. "на месте"
reverse(v::Vector)::Vector = v[end:-1:begin]

#Задача 10. Написать функцию, осуществляющую циклический сдвиг массива на m позиций "на месте", т.е. без использования дополнительного массива.
function cyclshift(a::AbstractVector, k::Integer) 
    reverse!(a)
    reverse!(@view a[begin:begin+k])
    reverse!(@view a[begin+k+1:end])
end

#Задача 11. Реализовать функцию, аналогичную встроенной функции transpose, с использованием вспомогательного массива
function transpose(V::Vector)::Vector
    len = length(V)
    Temp = copy(V)
    count = 0
    for i in (1:len)
        for j in (count+1:len)
            Temp[i][j], Temp[j][i] = Temp[j][i], Temp[i][j]
        end
        count += 1
    end
    return Temp
end