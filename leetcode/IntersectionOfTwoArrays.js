/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[]}
 */
var intersection = function(nums1, nums2) {
    let comp = (a, b) => a - b;
    nums1.sort(comp);
    nums2.sort(comp);
    let result = [];
    for (let i = 0, j = 0; i < nums1.length && j < nums2.length; ) {
        //console.log("i = " + i + ", j = " + j + ", nums1[i] = " + nums1[i] + ", nums2[j] = " + nums2[j]);
        if (nums1[i] == nums2[j]) {
            if (result.length == 0 || result[result.length - 1] != nums1[i]) {
                result.push(nums1[i]);
            }
            i++;
            j++;
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else {
            j++;
        }
    }
    return result;
};
