public class RemoveLinkedListElements {
  public ListNode removeElements(ListNode head, int val) {
    ListNode pp = null;
    for (ListNode p = head; p != null; p = p.next) {
      if (p.val == val) {
        if (pp == null) {
          head = head.next;
        } else {
          pp.next = p.next;
        }
      } else {
        pp = p;
      }
    }
    return head;
  }
}
