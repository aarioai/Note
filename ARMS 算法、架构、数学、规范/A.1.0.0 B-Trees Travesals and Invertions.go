package main

import (
	"fmt"
	"sync"
)

type Node struct {
	N int
	L *Node
	R *Node
}

func merge(base []int, m []int) []int {
	a := make([]int, len(base)+len(m))
	copy(a, base)
	copy(a[len(base):], m)
	return a
}
func (node *Node) preorder() []int {
	r := []int{node.N}
	if node.L != nil {
		r = merge(r, node.L.preorder())
	}
	if node.R != nil {
		r = merge(r, node.L.preorder())
	}
	return r
}

func (node *Node) inorder() []int {
	r := []int{}
	if node.L != nil {
		r = merge(r, node.L.inorder())
	}
	r = append(r, node.N)
	if node.R != nil {
		r = merge(r, node.R.inorder())
	}
	return r
}

func (node *Node) postorder() []int {
	r := []int{}
	if node.L != nil {
		r = merge(r, node.L.postorder())
	}
	if node.R != nil {
		r = merge(r, node.R.postorder())
	}
	r = append(r, node.N)
	return r
}

type Queue struct {
	Data *Node
	Next *Queue
	Prev *Queue
}

func (queue *Queue) push(node *Node) {
	for {
		if queue.Next != nil {
			queue = queue.Next
			continue
		}

		if queue.Data != nil {
			panic("Must allocate an empty Queue memory space")
		}
		queue.Data = node
		break
	}
}

func (queue *Queue) reverse() {
	if queue == nil {
		return
	}

	for qp := queue.Prev; qp != nil; queue = queue.Prev {
	}

	for {
		if queue.Data == nil {
			if queue.Next == nil {
				break
			}
			queue = queue.Next
		}
		fmt.Print("Reverse: ")
		fmt.Println(queue.Data.N)
		if queue.Next != nil {
			queue = queue.Next
			continue
		}
		break
	}
}

func (queue *Queue) pop() *Node {
	if queue == nil {
		return nil
	}

	for {
		if queue.Prev != nil && queue.Prev.Data != nil {
			queue = queue.Prev
			continue
		}

		if queue.Next == nil {
			if queue.Data == nil {
				return nil
			}
			d := queue.Data
			queue.Data = nil
			return d
		} else {
			d := queue.Data
			queue = queue.Next
			queue.Prev = nil
			return d
		}
	}
	return nil
}

var sm *sync.Mutex

func (root *Node) levelorder() []int {
	sm = new(sync.Mutex)
	r := []int{}
	queue := new(Queue)
	sm.Lock()
	queue.push(root)
	sm.Unlock()
	for {
		sm.Lock()
		n := queue.pop()
		sm.Unlock()
		if n == nil {
			break
		}
		r = append(r, n.N)

		if n.L != nil {
			queue.Next = &Queue{Prev: queue}
			queue = queue.Next
			sm.Lock()
			queue.push(n.L)
			sm.Unlock()
		}
		if n.R != nil {
			queue.Next = &Queue{Prev: queue}
			queue = queue.Next
			sm.Lock()
			queue.push(n.R)
			sm.Unlock()
		}
	}

	return r
}

func (node *Node) invert() {
	if node == nil {
		return
	}
	tmp := node.L
	node.L = node.R
	node.R = tmp
	if node.L != nil {
		node.L.invert()
	}
	if node.R != nil {
		node.R.invert()
	}
}

func invertTree(node *Node) *Node {
	if node == nil {
		return node
	}
	l := node.L
	r := node.R
	if l != nil {
		node.R = invertTree(l)
	} else {
		node.R = nil
	}
	if r != nil {
		node.L = invertTree(r)
	} else {
		node.L = nil
	}
	return node
}

func main() {
	a := &Node{N: 4}
	c := &Node{N: 7}
	e := &Node{N: 8}
	d := &Node{N: 5, L: c, R: e}

	b := &Node{N: 2, L: a, R: d}

	h := &Node{N: 9}
	i := &Node{N: 6, L: h}
	g := &Node{N: 3, R: i}

	f := &Node{N: 1, L: b, R: g}

	fmt.Println(f.preorder())
	fmt.Println(f.inorder())
	fmt.Println(f.postorder())
	fmt.Println(f.levelorder())

	f.invert()
	fmt.Println(f.levelorder())

	fmt.Println(invertTree(f).levelorder())
}
