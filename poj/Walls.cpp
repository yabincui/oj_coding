// POJ 3470
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <vector>
using namespace std;

int N, M;

struct Wall {
  int x1, y1, x2, y2;
} walls[50000];

Wall normalized_walls[50000];

struct Point {
  int x, y;
} birds[50000];

Point normalized_birds[50000];

int hit_walls[50000];

void CHECK(bool value) {
  if (!value) {
    exit(0);
  }
}

void NormalizeXY() {
  for (int i = 0; i < N; ++i) {
    if (walls[i].x1 > walls[i].x2) {
      swap(walls[i].x1, walls[i].x2);
    }
    if (walls[i].y1 > walls[i].y2) {
      swap(walls[i].y1, walls[i].y2);
    }
  }

  vector<int> buffer;
  for (int i = 0; i < N; ++i) {
    buffer.push_back(walls[i].x1);
    buffer.push_back(walls[i].x2);
  }
  for (int i = 0; i < M; ++i) {
    buffer.push_back(birds[i].x);
  }
  sort(buffer.begin(), buffer.end());
  buffer.erase(unique(buffer.begin(), buffer.end()), buffer.end());
  for (int i = 0; i < N; ++i) {
    int nx1 = lower_bound(buffer.begin(), buffer.end(), walls[i].x1) - buffer.begin() + 1;
    int nx2 = lower_bound(buffer.begin(), buffer.end(), walls[i].x2) - buffer.begin() + 1;
    normalized_walls[i].x1 = nx1;
    normalized_walls[i].x2 = nx2;
  }
  for (int i = 0; i < M; ++i) {
    int nx = lower_bound(buffer.begin(), buffer.end(), birds[i].x) - buffer.begin() + 1;
    normalized_birds[i].x = nx;
  }
  buffer.clear();
  for (int i = 0; i < N; ++i) {
    buffer.push_back(walls[i].y1);
    buffer.push_back(walls[i].y2);
  }
  for (int i = 0; i < M; ++i) {
    buffer.push_back(birds[i].y);
  }
  sort(buffer.begin(), buffer.end());
  buffer.erase(unique(buffer.begin(), buffer.end()), buffer.end());
  for (int i = 0; i < N; ++i) {
    int ny1 = lower_bound(buffer.begin(), buffer.end(), walls[i].y1) - buffer.begin() + 1;
    int ny2 = lower_bound(buffer.begin(), buffer.end(), walls[i].y2) - buffer.begin() + 1;
    normalized_walls[i].y1 = ny1;
    normalized_walls[i].y2 = ny2;
  }
  for (int i = 0; i < M; ++i) {
    int ny = lower_bound(buffer.begin(), buffer.end(), birds[i].y) - buffer.begin() + 1;
    normalized_birds[i].y = ny;
  }
}

enum ItemType {
  StartOfWall,
  EndOfWall,
  Wall,
  Bird,
};

struct Item {
  int type;
  int value;
  int id; // wall_id or bird id.
} items[150000];

bool compareItem(const Item& item1, const Item& item2) {
  return item1.value < item2.value;
}

struct BirdTouch {
  int wall_id;
  int dist;
} bird_touch[50000];

struct SegmentTreeNode {
  int value;
} nodes[1 << 20];

void SetNodeValue(int root, int l, int r, int place, int value) {
  while (true) {
    CHECK(root < (1 << 20));
    if (l == r) {
      nodes[root].value = value;
      return;
    }
    int m = (l + r) / 2;
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    if (nodes[root].value != 0) {
      int t = nodes[root].value;
      nodes[root].value = 0;
      CHECK(left < (1 << 20));
      CHECK(right < (1 << 20));
      nodes[left].value = t;
      nodes[right].value = t;
    }
    if (place <= m) {
      root = left;
      r = m;
    } else {
      root = right;
      l = m + 1;
    }
  }
}

void SetNodeRangeValue(int root, int l, int r, int start, int end, int value) {
  CHECK(root < (1 << 20));
  if (l >= start && r <= end) {
    nodes[root].value = value;
    return;
  }
  if (l > end || r < start) {
    return;
  }
  int m = (l + r) / 2;
  int left = root * 2 + 1;
  int right = root * 2 + 2;
  if (nodes[root].value != 0) {
    int t = nodes[root].value;
    nodes[root].value = 0;
    CHECK(left < (1 << 20));
    CHECK(right < (1 << 20));
    nodes[left].value = t;
    nodes[right].value = t;
  }
  SetNodeRangeValue(root * 2 + 1, l, m, start, end, value);
  SetNodeRangeValue(root * 2 + 2, m + 1, r, start, end, value);
}

int GetNodeValue(int root, int l, int r, int place) {
  while (true) {
    CHECK(root < (1 << 20));
    if (nodes[root].value != 0 || l == r) {
      return nodes[root].value;
    }
    int m = (l + r) / 2;
    if (place <= m) {
      root = root * 2 + 1;
      r = m;
    } else {
      root = root * 2 + 2;
      l = m + 1;
    }
  }
}

void solve() {
  //fprintf(stderr, "t0\n");
  NormalizeXY();
  //fprintf(stderr, "t1\n");
  memset(hit_walls, 0, sizeof(hit_walls));
  memset(bird_touch, -1, sizeof(bird_touch));

  int node_count = 1;
  while (node_count < N * 2 + M) {
    node_count *= 2;
  }

  int t = 0;
  for (int i = 0; i < N; ++i) {
    if (walls[i].x1 == walls[i].x2) {
      items[t].type = Wall;
      items[t].value = walls[i].x1;
      items[t].id = i;
      t++;
    } else {
      items[t].type = StartOfWall;
      items[t].value = walls[i].x1;
      items[t].id = i;
      t++;
      items[t].type = EndOfWall;
      items[t].value = walls[i].x2;
      items[t].id = i;
      t++;
    }
  }
  for (int i = 0; i < M; ++i) {
    items[t].type = Bird;
    items[t].value = birds[i].x;
    items[t].id = i;
    t++;
  }
  sort(items, items + t, compareItem);
  //fprintf(stderr, "t2\n");
  // Let the bird fly to left, and we go from left to right.
  memset(nodes, 0, sizeof(nodes));
  for (int i = 0; i < t; ++i) {
    if (items[i].type == Wall) {
      int id = items[i].id;
      //printf("SetNodeRangeValue(0, 0, %d, %d, %d, %d)\n", node_count - 1, normalized_walls[id].y1,
      //    normalized_walls[id].y2, id + 1);
      SetNodeRangeValue(0, 0, node_count - 1, normalized_walls[id].y1, normalized_walls[id].y2, id + 1);
      //printf("end\n");
    } else if (items[i].type == EndOfWall) {
      int id = items[i].id;
      //printf("SegNodeValue(0, 0, %d, %d, %d)\n", node_count - 1, normalized_walls[id].y1, id + 1);
      SetNodeValue(0, 0, node_count - 1, normalized_walls[id].y1, id + 1);
      //printf("end\n");
    } else if (items[i].type == Bird) {
      int id = items[i].id;
      //printf("GetNodeValue(0, 0, %d, %d)\n", node_count - 1, normalized_birds[id].y);
      int value = GetNodeValue(0, 0, node_count - 1, normalized_birds[id].y);
      //printf("end value = %d\n", value);
      if (value != 0) {
        int wall_id = value - 1;
        int dist = birds[id].x - walls[wall_id].x2;
        //printf("bird %d fly to left to wall %d, dist %d\n", id, wall_id, dist);
        if (bird_touch[id].wall_id == -1 || bird_touch[id].dist > dist) {
          bird_touch[id].wall_id = wall_id;
          bird_touch[id].dist = dist;
        }
      }
    }
  }
  //fprintf(stderr, "t3\n");
  // Let the bird fly to right, and we go from right to left.
  memset(nodes, 0, sizeof(nodes));
  for (int i = t - 1; i >= 0; --i) {
    if (items[i].type == Wall) {
      int id = items[i].id;
      SetNodeRangeValue(0, 0, node_count - 1, normalized_walls[id].y1, normalized_walls[id].y2, id + 1);
    } else if (items[i].type == StartOfWall) {
      int id = items[i].id;
      SetNodeValue(0, 0, node_count - 1, normalized_walls[id].y1, id + 1);
    } else if (items[i].type == Bird) {
      int id = items[i].id;
      int value = GetNodeValue(0, 0, node_count - 1, normalized_birds[id].y);
      if (value != 0) {
        int wall_id = value - 1;
        int dist = walls[wall_id].x1 - birds[id].x;
        if (bird_touch[id].wall_id == -1 || bird_touch[id].dist > dist) {
          bird_touch[id].wall_id = wall_id;
          bird_touch[id].dist = dist;
        }
      }
    }
  }
  t = 0;
  for (int i = 0; i < N; ++i) {
    if (walls[i].y1 == walls[i].y2) {
      items[t].type = Wall;
      items[t].value = walls[i].y1;
      items[t].id = i;
      t++;
    } else {
      items[t].type = StartOfWall;
      items[t].value = walls[i].y1;
      items[t].id = i;
      t++;
      items[t].type = EndOfWall;
      items[t].value = walls[i].y2;
      items[t].id = i;
      t++;
    }
  }
  for (int i = 0; i < M; ++i) {
    items[t].type = Bird;
    items[t].value = birds[i].y;
    items[t].id = i;
    t++;
  }
  sort(items, items + t, compareItem);
  // Let the bird fly to down, and we go from bottom to up. 
  memset(nodes, 0, sizeof(nodes));
  for (int i = 0; i < t; ++i) {
    if (items[i].type == Wall) {
      int id = items[i].id;
      SetNodeRangeValue(0, 0, node_count - 1, normalized_walls[id].x1, normalized_walls[id].x2, id + 1);
    } else if (items[i].type == EndOfWall) {
      int id = items[i].id;
      SetNodeValue(0, 0, node_count - 1, normalized_walls[id].x1, id + 1);
    } else if (items[i].type == Bird) {
      int id = items[i].id;
      int value = GetNodeValue(0, 0, node_count - 1, normalized_birds[id].x);
      if (value != 0) {
        int wall_id = value - 1;
        int dist = birds[id].y - walls[wall_id].y2;
        if (bird_touch[id].wall_id == -1 || bird_touch[id].dist > dist) {
          bird_touch[id].wall_id = wall_id;
          bird_touch[id].dist = dist;
        }
      }
    }
  }
  // Let the bird fly to up, and we go from up to bottom. 
  memset(nodes, 0, sizeof(nodes));
  for (int i = t - 1; i >= 0; --i) {
    if (items[i].type == Wall) {
      int id = items[i].id;
      SetNodeRangeValue(0, 0, node_count - 1, normalized_walls[id].x1, normalized_walls[id].x2, id + 1);
    } else if (items[i].type == StartOfWall) {
      int id = items[i].id;
      SetNodeValue(0, 0, node_count - 1, normalized_walls[id].x1, id + 1);
    } else if (items[i].type == Bird) {
      int id = items[i].id;
      int value = GetNodeValue(0, 0, node_count - 1, normalized_birds[id].x);
      if (value != 0) {
        int wall_id = value - 1;
        int dist = walls[wall_id].y1 - birds[id].y;
        if (bird_touch[id].wall_id == -1 || bird_touch[id].dist > dist) {
          bird_touch[id].wall_id = wall_id;
          bird_touch[id].dist = dist;
        }
      }
    }
  }
  for (int i = 0; i < M; ++i) {
    int wall_id = bird_touch[i].wall_id;
    CHECK(wall_id != -1);
    //printf("bird[%d], hit_wall %d\n", i, wall_id);
    hit_walls[wall_id]++;
  }
  for (int i = 0; i < N; ++i) {
    printf("%d\n", hit_walls[i]);
  }
}

int main() {
  freopen("Walls.in", "r", stdin);
  scanf("%d%d", &N, &M);
  for (int i = 0; i < N; ++i) {
    scanf("%d%d%d%d", &walls[i].x1, &walls[i].y1, &walls[i].x2, &walls[i].y2);
  }
  for (int i = 0; i < M; ++i) {
    scanf("%d%d", &birds[i].x, &birds[i].y);
  }
  solve();
  return 0;
}
