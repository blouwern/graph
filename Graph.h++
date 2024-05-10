#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <list>
#include <memory_resource>
#include <unordered_map>
#include <utility>

namespace WZC {

/// @brief Tag type indicates the graph is unweighted.
struct Unweighted {};

/// @brief A finite, simple, undirected, weighted/unweighted graph.
/// @tparam T value type on vertex
/// @tparam W weight type on edge
template<typename T, typename W = Unweighted>
class Graph {
public:
    class Vertex;
    class Edge;

    using VertexListType = std::pmr::list<Vertex>;
    using EdgeListType = std::pmr::list<Edge>;

    using VertexIterator = typename VertexListType::iterator;
    using EdgeIterator = typename EdgeListType::iterator;

    using VertexConstIterator = typename VertexListType::const_iterator;
    using EdgeConstIterator = typename EdgeListType::const_iterator;

protected:
    using MemoryPool = std::pmr::unsynchronized_pool_resource;

public:
    /// @brief Graph vertex.
    class Vertex {
        friend class Graph;

    protected:
        Vertex(const T& value, MemoryPool& memoryPool) :
            fValue{value},
            fNeighborList{&memoryPool} {}

        Vertex(T&& value, MemoryPool& memoryPool) :
            fValue{std::move(value)},
            fNeighborList{&memoryPool} {}

        Vertex(const Vertex&) = delete;
        auto operator=(const Vertex&) -> Vertex& = delete;

    public:
        ~Vertex() {
            // TODO
        }

        auto operator*() const -> const T& { return fValue; }
        auto operator*() -> T& { return fValue; }

        auto operator->() const -> const T* { return &fValue; }
        auto operator->() -> T* { return &fValue; }

        auto NeighborList() const -> const auto& { return fNeighborList; }

    private:
        struct HashVertexIterator {
            auto operator()(VertexIterator it) const -> std::size_t {
                return reinterpret_cast<std::uintptr_t>(&*it);
            }
        };

    private:
        T fValue;

        VertexIterator fSelf;
        std::pmr::unordered_map<VertexIterator, EdgeIterator, HashVertexIterator> fNeighborList;
    };

    /// @brief Graph edge
    class Edge {
        friend class Graph;

    protected:
        Edge(Vertex& vertex1, Vertex& vertex2, const W& weight) :
            fVertex1{vertex1},
            fVertex2{vertex2},
            fWeight{weight} {}

        Edge(Vertex& vertex1, Vertex& vertex2, W&& weight) :
            fVertex1{vertex1},
            fVertex2{vertex2},
            fWeight{std::move(weight)} {}

        Edge(const Edge&) = delete;
        auto operator=(const Edge&) -> Edge& = delete;

    public:
        ~Edge() {
            // TODO
        }

        auto Vertex1() const -> const Vertex& { return fVertex1; }
        auto Vertex2() const -> const Vertex& { return fVertex2; }
        auto Weight() const -> const W& { return fWeight; }

        auto Vertex1() -> Vertex& { return fVertex1; }
        auto Vertex2() -> Vertex& { return fVertex2; }
        auto Weight() -> W& { return fWeight; }

    private:
        Vertex& fVertex1;
        Vertex& fVertex2;
        W fWeight;
    };

public:
    Graph() :
        fMemoryPool{},
        fVertexList{&fMemoryPool},
        fEdgeList{&fMemoryPool} {}

    /// @brief Add a vertex to this graph.
    /// @param value value on the vertex to be added.
    /// @return An iterator to the vertex added.
    auto AddVertex(const T& value) -> VertexIterator {
        return AddVertexImpl({value, fMemoryPool});
    }

    /// @brief Add a vertex to this graph.
    /// @param value value on the vertex to be added.
    /// @return An iterator to the vertex added.
    auto AddVertex(T&& value) -> VertexIterator {
        return AddVertexImpl({std::move(value), fMemoryPool});
    }

    /// @brief Add an edge to this graph
    /// @param vertex1 an vertex on edge
    /// @param vertex2 another vertex on edge
    /// @param weight edge weight
    /// @return An iterator to the edge added.
    auto AddEdge(Vertex& vertex1, Vertex& vertex2, const W& weight) -> EdgeIterator {
        return AddEdgeImpl(vertex1, vertex2, weight);
    }

    /// @brief Add an edge to this graph
    /// @param vertex1 an vertex on edge
    /// @param vertex2 another vertex on edge
    /// @param weight edge weight
    /// @return An iterator to the edge added.
    auto AddEdge(Vertex& vertex1, Vertex& vertex2, W&& weight = {}) -> EdgeIterator {
        return AddEdgeImpl(vertex1, vertex2, std::move(weight));
    }

    /// @brief Add an edge to this graph
    /// @param vertex1 an vertex (iterator) on edge
    /// @param vertex2 another vertex (iterator) on edge
    /// @param weight edge weight
    /// @return An iterator to the edge added.
    auto AddEdge(VertexIterator vertex1, VertexIterator vertex2, const W& weight) -> EdgeIterator {
        return AddEdge(*vertex1, *vertex2, weight);
    }

    /// @brief Add an edge to this graph
    /// @param vertex1 an vertex (iterator) on edge
    /// @param vertex2 another vertex (iterator) on edge
    /// @param weight edge weight
    /// @return An iterator to the edge added.
    auto AddEdge(VertexIterator vertex1, VertexIterator vertex2, W&& weight = {}) -> EdgeIterator {
        return AddEdge(*vertex1, *vertex2, std::move(weight));
    }

    auto VertexList() const -> const auto& { return fVertexList; }
    auto EdgeList() const -> const auto& { return fEdgeList; }

protected:
    auto AddVertexImpl(Vertex&& vertex) -> VertexIterator {
        // TODO
    }

    auto AddEdgeImpl(Vertex& vertex1, Vertex& vertex2, std::convertible_to<W> auto&& weight) -> EdgeIterator {
        // TODO
    }

protected:
    MemoryPool fMemoryPool;

    VertexListType fVertexList;
    EdgeListType fEdgeList;
};

} // namespace WZC
