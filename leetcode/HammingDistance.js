/**
 * @param {number} x
 * @param {number} y
 * @return {number}
 */
var hammingDistance = function(x, y) {
    let res = 0;
    for (let i = 0; i <= 31; ++i) {
        let bit = 1 << i;
        if ((x & bit) != (y & bit)) {
            res++;
        }
    }
    return res;
};
