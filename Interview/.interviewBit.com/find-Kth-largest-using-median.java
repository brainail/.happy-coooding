public static int findKthLargestUsingMedian(Integer[] array, int k) {
        // Step 1: Divide the list into n/5 lists of 5 element each.
        int noOfRequiredLists = (int) Math.ceil(array.length / 5.0);
        // Step 2: Find pivotal element aka median of medians.
        int medianOfMedian =  findMedianOfMedians(array, noOfRequiredLists);
        //Now we need two lists split using medianOfMedian as pivot. All elements in list listOne will be grater than medianOfMedian and listTwo will have elements lesser than medianOfMedian.
        List<Integer> listWithGreaterNumbers = new ArrayList<>(); // elements greater than medianOfMedian
        List<Integer> listWithSmallerNumbers = new ArrayList<>(); // elements less than medianOfMedian
        for (Integer element : array) {
            if (element < medianOfMedian) {
                listWithSmallerNumbers.add(element);
            } else if (element > medianOfMedian) {
                listWithGreaterNumbers.add(element);
            }
        }
        // Next step.
        if (k <= listWithGreaterNumbers.size()) return findKthLargestUsingMedian((Integer[]) listWithGreaterNumbers.toArray(new Integer[listWithGreaterNumbers.size()]), k);
        else if ((k - 1) == listWithGreaterNumbers.size()) return medianOfMedian;
        else if (k > (listWithGreaterNumbers.size() + 1)) return findKthLargestUsingMedian((Integer[]) listWithSmallerNumbers.toArray(new Integer[listWithSmallerNumbers.size()]), k-listWithGreaterNumbers.size()-1);
        return -1;
    }

    public static int findMedianOfMedians(Integer[] mainList, int noOfRequiredLists) {
        int[] medians = new int[noOfRequiredLists];
        for (int count = 0; count < noOfRequiredLists; count++) {
            int startOfPartialArray = 5 * count;
            int endOfPartialArray = startOfPartialArray + 5;
            Integer[] partialArray = Arrays.copyOfRange((Integer[]) mainList, startOfPartialArray, endOfPartialArray);
            // Step 2: Find median of each of these sublists.
            int medianIndex = partialArray.length/2;
            medians[count] = partialArray[medianIndex];
        }
        // Step 3: Find median of the medians.
        return medians[medians.length / 2];
    }


    /*
    public static int findKthLargestUsingPriorityQueue(Integer[] nums, int k) {
        int p = 0;
        int numElements = nums.length;
        // create priority queue where all the elements of nums will be stored
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>();

        // place all the elements of the array to this priority queue
        for (int n : nums) {
            pq.add(n);
        }

        // extract the kth largest element
        while (numElements - k + 1 > 0) {
            p = pq.poll();
            k++;
        }

        return p;
    }
    */