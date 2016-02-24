void delBdoubA(string &s){
    //wr is the write head, pointing to the next character to be overwritten if it's not b. if string Sb+, wr points
    //to first b, else points to one car ahead of the last char
    int wr=0,ac=0;
    for(char &c : s){
        if(c!='b'){
            s[wr++]=c;
        }
        if(c=='a'){
            ac++;    
        }
    }
    s.resize(wr+ac);
    int ci=wr-1;
    wr=s.size()-1;
    while(ci>=0){
        if(s[ci]=='a'){
            s[wr--]=s[wr--]='d';
            ci--;
        } 
        else
            s[wr--]=s[ci--];
    }
}