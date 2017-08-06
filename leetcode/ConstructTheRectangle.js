/**
 * @param {number} area
 * @return {number[]}
 */
var constructRectangle = function(area) {
    if (area == 0) {
        return [0, 0];
    }
    if (area == 1) {
        return [1, 1];
    }
    let max = Math.floor(Math.sqrt(area));
    for (let i = max; i >= 1; --i) {
        if (area % i == 0) {
            return [area / i, i];
        }
    }
    
};
