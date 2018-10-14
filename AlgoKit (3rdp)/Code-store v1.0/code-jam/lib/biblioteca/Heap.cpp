struct Heap{
	pair<int, int> heap[230];
	int pos[230];
	int neltos;
	Heap(){
		neltos =0;
		memset(pos,-1,sizeof(pos));
	}
	
	pair<int, int> top(){
		return heap[1];
	}
	
	bool empty(){
		return neltos == 0;
	}
	
	void swap(int a, int b){
		pair<int, int> aux;
        pos[heap[a].second] = b;
		pos[heap[b].second] = a;
		aux = heap[a];
		heap[a] = heap[b];
		heap[b] = aux;
	}
	
	void push( pair <int, int> novo){
		int posicao;
		if(pos[novo.second] == -1){
			neltos++;
			heap[neltos] = novo;
			pos[novo.second] = neltos;
		}
		heap[pos[novo.second]].first = novo.first;
		posicao = pos[novo.second];
		while(posicao > 1){
			if(heap[posicao].first > heap[posicao/2].first){
				swap(posicao, posicao/2);
				posicao /= 2;
			}else break;
		}
	}
	
	void heapfy(int posicao){
		int p1;
		while((posicao*2) <= neltos){
			p1 = posicao*2;
			if((p1 + 1) <= neltos){
				if(heap[p1].first < heap[(p1 + 1)].first)p1++;
			}
			if(heap[posicao].first < heap[p1].first){
				swap(posicao,p1);
				posicao = p1;
			}else break;
		}
	}
	
	void pop(){
		pos[heap[1].second] = -1;
		neltos--;
		if(neltos == 0)return;
		pos[heap[neltos+1].second] = 1;
		heap[1] = heap[neltos+1];
		heapfy(1);
	}
	
};
