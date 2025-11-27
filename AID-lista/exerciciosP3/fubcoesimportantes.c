Node* menor(Node* root){
    while (root->left != NULL)
        root = root->left;
    return root;
}

Node* removeT(Node* root, int valor){
    if (root == NULL) return NULL;

    if (valor < root->dado)
        root->left = removeT(root->left, valor);

    else if (valor > root->dado)
        root->right = removeT(root->right, valor);

    else {
        // Caso 1: sem filhos
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }

        // Caso 2: só 1 filho
        if (root->left == NULL) {
            return root->right;
        }
        if (root->right == NULL) {
            return root->left;
        }

        // Caso 3: dois filhos → sucessor
        Node* temp = menor(root->right);
        root->dado = temp->dado;
        root->right = removeT(root->right, temp->dado);
    }

    return root;
}




Node* maior(Node* root){
    while (root->right != NULL)
        root = root->right;
    return root;
}

Node* removeT(Node* root, int valor){
    if (root == NULL) return NULL;

    if (valor < root->dado)
        root->left = removeT(root->left, valor);

    else if (valor > root->dado)
        root->right = removeT(root->right, valor);

    else {
        // Caso 1: nó folha
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }

        // Caso 2: só 1 filho
        if (root->left == NULL) {
            return root->right;
        }
        if (root->right == NULL) {
            return root->left;
        }

        // Caso 3: dois filhos → PREDECESSOR (maior da esquerda)
        Node* temp = maior(root->left);
        root->dado = temp->dado;
        root->left = removeT(root->left, temp->dado);
    }

    return root;
}

Node* pushT(Node* root, int num){
    if (root == NULL){
        Node* novo = (Node*) malloc(sizeof(Node));
        novo->n = num;
        novo->left = novo->right = NULL;
        return novo;
    }

    if (root->n > num) root->left = pushT(root->left, num);
    else root->right = pushT(root->right, num);

    return root;
}

int searchT(Node* root, int num) {
    while (root != NULL) {
        if (num == root->valor) return 1;
        if (num < root->valor) root = root->left;
        else root = root->right;
    }
    return 0;
}

/* ---------------------------------------
   QUICKSORT
----------------------------------------*/

void swap(int* a, int* b) {
    int x = *a;
    *a = *b;
    *b = x;
}

int partition(int v[], int low, int high) {
    int pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (v[j] <= pivot) {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[high]);
    return i + 1;
}

void quickSort(int v[], int low, int high) {
    if (low < high) {
        int pi = partition(v, low, high);
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}


int binarySearch(int v[], int n, int target) {
    int left = 0, right = n - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (v[mid] == target) return 1;
        if (target < v[mid]) right = mid - 1;
        else left = mid + 1;
    }

    return 0;
}


no *busca (Arvore A, int k) {
if (A == NULL || A->chave == k)
return A;
if ( k < A->chave)
return busca (A->esq, k);
else
return busca (A->dir, k);
}

Busca o elemento 4

no *busca ( Arvore A, int k ) {
while ( A != NULL || A->chave != k) {
if (A->chave > k)
A = A->esq;
else
A = A->dir;
}
return A;
}

Arvore insere (Arvore A, int k) {
no* novo;
novo = (no*) malloc (sizeof(no));
novo->chave = k;
novo->esq = novo->dir = NULL;
no *antep,

*ultimo;

if ( A == NULL ) return novo;
ultimo = A;
while( ultimo != NULL) {
antep = ultimo;
if ( ultimo->chave > k ) ultimo = ultimo->esq;
else ultimo = ultimo->dir;
}
if ( antep->chave > k ) antep->esq = novo;
else antep->dir = novo;
return A;
}