

void inserirSubArvo (No *a, int valor){
    if (no -> valor < valor){
        //vou tentar inserir à esquerda
        if (no -> esquerda == NULL){
            inserirSubArvo(no -> esquerda, valor);
        }
    }
    else{
        // [vou tentar inserir a direita
        inserirSubArvo(no -> direito, valor);
    }
}

void inserirArvore(No *a, int valor){
    if (a -> raiz == NULL){
        a -> raiz = newNo(valor);
    }
    else if (a -> raiz -> valor < valor){
        // vou tentar inserir à esquerda
        if (a -> raiz -> esquerda == NULL){
            a -> raiz -> esquerda = newNo(valor);
        }
    }
    else{
        // vou tentar inserir a direita
        if (a -> raiz -> direita == NULL){
            a -> raiz -> direita = newNo(valor);
        }
    }
}

No* buscarSubArvore (Arvore *a, int valor){
    if (no -> valor == valor) return no;
    if(no -> valor > valor){
        //busca à esquerda
    }
}
int main(){
    No *no01
}