/**
 * @param {number} num
 * @return {number}
 */
var addDigits = function(num) {
    while (num >= 10) {
        let sum = 0;
        while (num != 0) {
            sum += num % 10;
            num = Math.trunc(num / 10);
        }
        //console.log("sum = " + sum);
        num = sum;
    }
    return num;
};
