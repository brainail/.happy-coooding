std::vector<int> mergeKArrays(std::vector<std::vector<int>> arrays)
{
    std::vector<int> firstUnused(arrays.size(), 0),
        result;
    int n = 0;
    for (int i = 0; i < arrays.size(); i++)
    {
        n += arrays[i].size();
    }
    for (int i = 0; i < n; i++)
    {
        int minIndex = -1,
            minValue = 0;
        for (int j = 0; j < arrays.size(); j++)
        {
            if (firstUnused[j] < arrays[j].size())
            {
                if (arrays[j][firstUnused[j]] < minValue || -1 == minIndex)
                {
                    minIndex = j;
                    minValue = arrays[j][firstUnused[j]];
                }
            }
        }
        result.push_back(minValue);
        firstUnused[minIndex]++;
    }
    return result;
}
