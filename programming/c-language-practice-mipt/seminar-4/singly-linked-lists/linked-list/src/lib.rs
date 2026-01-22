#![allow(unused)]

use std::fmt::Debug;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn push() {
        let mut list = LinkedList::new();
        list.push(1729);
        let mut curr = &mut list.head;
        while curr.as_ref().unwrap().next.is_some() {
            curr = &mut curr.as_mut().unwrap().next;
        }
        assert_eq!(curr.take().map(|n| n.val), Some(1729));
        assert_eq!(list.length, 1);
    }

    #[test]
    fn pop() {
        let mut list = LinkedList::new();
        list.push(32);
        list.push(11);
        assert_eq!(list.length, 2);
        let value = list.pop();
        assert_eq!(list.length, 1);
        assert_eq!(value, Some(11));
        let value = list.pop();
        assert_eq!(list.length, 0);
        assert_eq!(value, Some(32));
    }
}

pub struct LinkedList<T> {
    pub length: usize,
    pub head: Option<Box<Node<T>>>,
}

pub struct Node<T> {
    val: T,
    next: Option<Box<Node<T>>>,
}

impl<T> Node<T> {
    fn new(val: T) -> Box<Self> {
        Box::new(Self { val, next: None })
    }
}

impl<T> LinkedList<T> {
    pub fn new() -> Self {
        Self {
            length: 0,
            head: None,
        }
    }
    pub fn push(&mut self, val: T) {
        let mut new_node = Node::new(val);
        if self.head.is_none() {
            self.head = Some(new_node);
        } else {
            let mut curr = &mut self.head;
            while let Some(node) = curr {
                if node.next.is_none() {
                    node.next = Some(new_node);
                    break;
                }
                curr = &mut node.next;
            }
        }
        self.length += 1;
    }
    pub fn pop(&mut self) -> Option<T> {
        if self.length == 0 {
            return None;
        } else if self.length == 1 {
            self.length -= 1;
            return self.head.take().map(|node| node.val);
        }
        self.length -= 1;
        let mut curr = &mut self.head;
        while curr.as_ref()?.next.is_some() {
            curr = &mut curr.as_mut()?.next;
        }
        curr.take().map(|node| node.val)
    }
}

impl<T: Debug> Debug for LinkedList<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let mut curr = &self.head;
        let mut vec = Vec::new();
        while let Some(node) = curr {
            vec.push(&node.val);
            curr = &node.next;
        }
        f.debug_list().entries(vec).finish()
    }
}
