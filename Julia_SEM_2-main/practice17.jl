#Задача 1. Написать и протестировать функцию, получающую на вход список смежностей некоторого графа, и возвращающую вектор индексов его вершин, полученных в порядке поиска в глубину.Указание. За основу взять соответствующий код, разобранный в лекции 8.
function dfsearch(startver::T, graph::ConnectList{T}) where T
    mark = zeros(Bool, length(graph))
    stack  = [startver] #стек обрабатываемых вершин
    mark[startver] = 1 #отмечаем, что были в вершине
    visited = Int64[] #посещенные вершниы
    while !isempty(stack)
        v = pop!(stack) #берем вершину
        push!(visited,v) #отмечаем, что были
        for u in graph[v]
            if mark[u] == 0
                push!(stack,u) #закидываем смежные вершины
                mark[u] = 1
            end
        end
    end
    return visited
end

#Задача 2. Написать и протестировать функцию, получающую на вход список смежностей некоторого графа, и возвращающую вектор индексов его вершин, полученных в порядке поиска в ширину.
function bfsearch(startver::T, graph::ConnectList{T}) where T
    mark = zeros(Bool, length(graph))
    queue  = [startver]
    mark[startver] = 1
    visited = Int64[]
    while !isempty(queue)
        v = popfirst!(queue)
        push!(visited,v)
        for u in graph[v]
            if mark[u] == 0
                push!(queue, u)
                mark[u] = 1
            end
        end
    end
    return visited
end

#Задача 3. Написать и протестировать функцию, получающую на вход список смежностей некоторого графа, и возвращающую вектор валентностей его вершин по выходу.
function valence(graph::ConnectList{T}) where T
    val = zeros(size(graph,1))
    for i in 1:size(graph,1)
        val[i]=length(graph[i])
    end
    return val
end

#Задача 4. Написать и протестировать функцию, получающую на вход список смежностей некоторого графа, и возвращающую вектор валентностей его вершин по входу.
function bfs_valence(graph::ConnectList{T}) where T
    mark = zeros(Int64, length(graph))
    queue  = [1]
    mark[1] = 1
    while !isempty(queue)
        v = popfirst!(queue) #обрабатываем первый элемент очереди
        #println(v)
        for u in graph[v]
            if mark[u] == 0
                push!(queue, u) #закидываем в очередь след элемент, если его не посещали
            end
            mark[u] = mark[u] + 1
        end
    end
    mark[1] -= 1
    return mark
end

#Задача 5. Написать и протестировать функцию, получающую на вход список смежностей некоторого графа, и возвращающую значение true, если он является сильно связным, и значение false - в противном случае.
function strongly_connected(graph::ConnectList)
    for s in 1:length(graph)
        if all_achievable(s, graph) == false
            return false
        end
    end
    return true
end

function attempt_achievable!(start_ver::T, graph::ConnectList{T}, mark::AbstractVector{<:Integer}) where T   
    stack  = [start_ver]
    mark[start_ver] = 1 
    while !isempty(stack)
        v = pop!(stack)
        for u in graph[v]
            if mark[u] == 0
                push!(stack,u)
                mark[u] = 1
            end
        end
    end
end

function all_achievable(started_ver::Integer, graph::ConnectList)
    mark = zeros(Bool,length(graph))
    attempt_achievable!(started_ver, graph, mark)
    return count(m->m==0, mark) == 0 #all(mark .== 1)
end

#Задача 6. Написать и протестировать функцию, получающую на вход список смежностей некоторого графа, и возвращающую значение true, если он является слабо связным, и значение false - в противном случае.
function strongly_connected(graph::ConnectList)
    for s in 1:length(graph)
        if all_achievable(s, graph) == false
            return true # слабо связный
        end
    end
    return false #сильно связный
end