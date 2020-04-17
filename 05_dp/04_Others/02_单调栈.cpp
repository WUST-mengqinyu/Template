// 求左边第一个比a[i]小的和右边最后一个不比a[i]小的位置
for (int i = 1; i <= n; i++) {
    while (top && a[sta[top - 1]] >= a[i]) top--;
    la[i] = (top == 0) ? 1 : sta[top - 1] + 1;
    sta[top++] = i;
}
top = 0;
for (int i = n; i >= 1; i--) {
    while (top && a[sta[top - 1]] >= a[i]) top--;
    ra[i] = (top == 0) ? n : sta[top - 1] - 1;
    sta[top++] = i;
}