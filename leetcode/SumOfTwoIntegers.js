/**
 * @param {number} a
 * @param {number} b
 * @return {number}
 */
var getSum = function(a, b) {
    
    function add(a, b) {
        if (a == 0) {
            return b;
        }
        if (b == 0) {
            return a;
        }
        let a1 = a & 1;
        let b1 = b & 1;
        let c = add(a >> 1, b >> 1);
        if (a1 && b1) {
            c = add(c, 1) << 1;
        } else {
            c = (c << 1) | a1 | b1;
        }
        return c;
    }
    
    function sub(a, b) {
        if (a == 0) {
            return -b;
        }
        if (b == 0) {
            return a;
        }
        let a1 = a & 1;
        let b1 = b & 1;
        let c = sub(a >> 1, b >> 1);
        if (a1 == b1) {
            return c << 1;
        }
        if (a1) {
            return (c << 1) | a1;
        }
        return (sub(c, 1) << 1) | 1;
    }
    
    let sign_a = a >= 0 ? 1 : -1;
    let sign_b = b >= 0 ? 1 : -1;
    let abs_a = a >= 0 ? a : -a;
    let abs_b = b >= 0 ? b : -b;
    
    if (sign_a == sign_b) {
        abs_a = add(abs_a, abs_b);    
    } else {
        if (abs_a > abs_b) {
            abs_a = -sub(abs_b, abs_a);
        } else {
            abs_a = sub(abs_a, abs_b);
        }
    }
    
    if (sign_a == -1) {
        abs_a = -abs_a;
    }
    return abs_a;
};
