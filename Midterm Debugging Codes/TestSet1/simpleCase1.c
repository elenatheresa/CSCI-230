// fix this dead loop
// the condition (!(value==10) || !(value==20)) cannot be arbitrarily changed.
// You are only allowed to change two characters on the condition (!(value==10) || !(value==20))
int value;
do
{
  value=10;
}while(!(value==10) || !(value==20))