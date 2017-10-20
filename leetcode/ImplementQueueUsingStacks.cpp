class MyQueue {
    
    stack<int> sIn;
    stack<int> sOut;
    
    void move() {
        if (!sOut.empty()) {
            return;
        }
        while (!sIn.empty()) {
            int val = sIn.top();
            sIn.pop();
            sOut.push(val);
        }
    }
    
public:
    /** Initialize your data structure here. */
    MyQueue() {
        
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        sIn.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        move();
        int val = sOut.top();
        sOut.pop();
        return val;
    }
    
    /** Get the front element. */
    int peek() {
        move();
        return sOut.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return sIn.empty() && sOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = new MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */