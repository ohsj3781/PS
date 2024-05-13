#include <iostream>
#include <vector>
#include <string>

std::vector<int> inorder;

const int find_upper_index(const int left, const int right, const int value)
{
    for (int i = left; i <= right; i++)
    {
        if (inorder[i] > value)
            return i;
    }
    return -1;
}

const int find_lower_index(const int left, const int right, const int value)
{
    for (int i = right; i >= left; i--)
    {
        if (inorder[i] < value)
            return i;
    }
    return -1;
}

void inorder_to_postorder(const int left, const int right)
{
    if (left > right)
        return;

    const int lower_index = find_lower_index(left + 1, right, inorder[left]);
    if (lower_index != -1)
    {
        inorder_to_postorder(left + 1, lower_index);
    }
    const int upper_index = find_upper_index(left + 1, right, inorder[left]);
    if (upper_index != -1)
    {
        inorder_to_postorder(upper_index, right);
    }
    std::cout<<inorder[left]<<'\n';
    return;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);

    int n;
    while (true)
    {
        std::cin >> n;
        if (std::cin.eof())
            break;
        inorder.push_back(n);
    }

    inorder_to_postorder(0, inorder.size() - 1);

    return 0;
}