@dnl = internal constant [4 x i8] c"%d\0A\00"
@d   = internal constant [4 x i8] c"%d\0A\00"
@emptyStr = internal constant [1 x i8] c"\00";

@errStr = internal constant [14 x i8] c"runtime error\00"

declare i32 @printf(i8*, ...) 
declare i32 @scanf(i8*, ...)
declare i32 @puts(i8*)
declare i64 @getline(i8**, i64*, %struct._IO_FILE*)

declare i8* @malloc(i32)
declare i32 @strlen(i8*)
declare i8* @strcpy(i8*, i8*)
declare i8* @strcat(i8*, i8*)
declare void @free(i8*)
declare void @exit(i32)
declare i32 @strcmp(i8*, i8*)



define void @printInt(i32 %x) {
       %t0 = getelementptr [4 x i8], [4 x i8]* @dnl, i32 0, i32 0
       call i32 (i8*, ...) @printf(i8* %t0, i32 %x) 
       ret void
}

define void @printString(i8* %s) {
entry:    
        call i32 @puts(i8* %s)
	ret void
}

define i32 @readInt() {
entry:	%res = alloca i32
        %t1 = getelementptr [4 x i8], [4 x i8]* @d, i32 0, i32 0
        call i32 (i8*, ...) @scanf(i8* %t1, i32* %res)
        %t2 = load i32, i32* %res
        ret i32 %t2
}

; This is ripped from http://ellcc.org/demo/index.cgi output of using getline
%struct._IO_FILE = type opaque
@stdin = external global %struct._IO_FILE*

define i8* @readString() {
entry:  
        %size = alloca i64
        store i64 0, i64* %size
        %ans = alloca i8*
        store i8* null, i8** %ans
        %in = load %struct._IO_FILE*, %struct._IO_FILE** @stdin

        %read = call i64 @getline(i8** %ans, i64* %size, %struct._IO_FILE* %in)
        %was_a_success = icmp ne i64 %read, -1
        br i1 %was_a_success, label %ValidRead, label %InvalidRead

ValidRead: 
        %ret = load i8*, i8** %ans
        %len = call i32 @strlen(i8* %ret)
        %len_sub = sub i32 %len, 1
        %last_char = getelementptr inbounds i8, i8* %ret, i32 %len_sub
        %loaded = load i8, i8* %last_char
        %loaded_i32 = sext i8 %loaded to i32
        %is_that_newline = icmp eq i32 %loaded_i32, 10
        br i1 %is_that_newline, label %Newline, label %NotNewline
        Newline:
                store i8 0, i8* %last_char
                ret i8* %ret
        NotNewline:
                ret i8* %ret
InvalidRead:
        %emptyStr = bitcast [1 x i8]* @emptyStr to i8*
        ret i8* %emptyStr
}

define void @error() {
        %str = getelementptr [14 x i8], [14 x i8]* @errStr, i32 0, i32 0
        call void @printString(i8* %str)
        call void @exit(i32 0)
        ret void
}

define i8* @concat(i8* %s1, i8* %s2)   {
entry:  
        %i1 = call i32 @strlen(i8* %s1)
        %i2 = call i32 @strlen(i8* %s2)
        %i3 = add i32 %i1, 1
        %i4 = add i32 %i3, %i2
        %i5 = call i8* @malloc(i32 %i4)
        %i6 = call i8* @strcpy(i8* %i5, i8* %s1)
        %i7 = call i8* @strcat(i8* %i6, i8* %s2)
        ret i8* %i7                            
}

define i32 @compare_strings(i8* %s1, i8* %s2) {
        %ans = call i32 @strcmp(i8* %s1, i8* %s2)
        ret i32 %ans
}