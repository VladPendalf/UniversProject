#Задача 1. Написать функцию convert_to_nested(tree::ConnectList{T}, root::T) where T, получающую на вход дерево, представленное списком смежностей tree и индексом его корня root, и возвращающая представление того же дерева в виде вложенных векторов.
ConnectList{T}=Vector{Vector{T}}
NestedVectors = Vector

function convert_to_nested(tree::ConnectList{T},root::T) where T
    nested_tree = []
    for subroot in tree[root]
        push!(nested_tree, convert(tree, subroot))
    end
    push!(nested_tree, root)
    return nested_tree
end

#---------ТЕСТ:
tree=[[2,3],
      [],
      [4,5],
      [],
      []]

nested_tree = convert_to_nested(tree, 1) 
println(nested_tree)  # Any[Any[2], Any[Any[4], Any[5], 3], 1] 

#Задача 2. Написать функцию convert_to_list(tree::NestedVectors), получающую на вход дерево, представленное вложенными векторами, и возвращающая кортеж из списка смежностей типа ConnectList этого дерева и индекса его корня.
function convert_to_dict(tree::NestedVectors)
    T=typeof(tree[end])
    connect_tree = Dict{T,Vector{T}}()
    
    function recurs_trace(tree)
        connect_tree[tree[end]]=[]
        for subtree in tree[1:end-1] # - перебор всех поддеревьев
            push!(connect_tree[tree[end]], recurs_trace(subtree))
        end
        return tree[end] # - индекс конрня
    end

    recurs_trace(tree)
    return connect_tree
end
function convert_to_list(tree::Dict{T,Vector{T}}) where T
    list_tree=Vector{Vector{T}}(undef,length(tree))
    for subroot in eachindex(list_tree)
        list_tree[subroot]=tree[subroot]
    end
    return list_tree
end
#Задача 4. Написать функцию convert(tree::Tree{T}) where T, получающую на вход ссылку на связанные структуры типа Tree{T}, представляющие некоторое дерево, и возвращающая кортеж из списка смежностей типа ConnectList этого дерева и индекса его корня.
function height(tree::ConnectList{T}, root::T) where T #функция, возвращающая высоту заданного дерева
    h=0
    for i in tree[root]
        h = max(h,height(tree,i))
    end
    return h+1
end

function vernumber(tree::ConnectList{T}) where T #функция, возвращаюшая число всех вершин заданного дерева
    return length(tree)
end

function leavesnumber(tree::ConnectList{T}, root::T) where T #функция, возвращающая число всех листьев заданного дерева
    if isempty(tree[root])
        return 1
    end
    N=0
    for i in tree[root]
        N += leavesnumber(tree,i)
    end
    return N
end

function maxvalence(tree::NestedVectors) #функция, возвращающая наибольшую валентность по выходу вершин заданного дерева
    mx = 0
    for i in 1:length(tree)
        mx = max(mx,length(tree[i][1]))
    end
    return mx
end

function sumpath_numver(tree::Tree) #функция, возвращающая среднюю длину пути к вершинам заданного дерева
    N = 1
    S = 1
    for sub in tree.sub
        s, n = sumpath_numver(sub)
        S += s + 1
        N += n
    end
    return S, N
end

#Задача 6Написать функцию, получающую на вход имя некоторого типа (встоенного или пользовательского) языка Julia (тип этого аргумента - Type) и распечатывающая список всех дочерних типов в следующем формате:
function alltypes(type)
    for i in subtypes(type)
        println(i)
        alltypes(i)
    end
end