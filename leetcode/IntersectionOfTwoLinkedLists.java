public class IntersectionOfTwoLinkedLists {
  public ListNode getIntersectionNode(ListNode headA, ListNode headB) {
    if (headA == null || headB == null) {
      return null;
    }
    ListNode newHeadA = reverseList(headA);
    ListNode end = headB;
    for (; end.next != null; end = end.next) {
    }
    boolean intersect = false;
    if (end == headA) {
      intersect = true;
    }
    int bHeadAHead = 0;
    if (intersect) {
      bHeadAHead = listLen(headB);
    }
    reverseList(newHeadA);
    if (!intersect) {
      return null;
    }
    int aLen = listLen(headA);
    int bLen = listLen(headB);
    int diffOfAHeadTail = bHeadAHead - bLen;
    int aHead = (aLen + diffOfAHeadTail) / 2;
    end = headA;
    for (int i = 0; i < aHead; ++i) {
      end = end.next;
    }
    return end;
  }

  ListNode reverseList(ListNode head) {
    ListNode pp = null;
    ListNode p = head;
    while (p != null) {
      ListNode np = p.next;
      p.next = pp;
      pp = p;
      p = np;
    }
    return pp;
  }

  int listLen(ListNode head) {
    int len = 0;
    for (; head != null; head = head.next, ++len) {
    }
    return len;
  }
}
