@dnl = internal constant [4 x i8] c"%d\0A\00"
@fnl = internal constant [6 x i8] c"%.1f\0A\00"
@d   = internal constant [4 x i8] c"%d\0A\00"
@str = internal constant [9 x i8] c"%[^\0A]%*c\00"

@errStr = internal constant [14 x i8] c"runtime error\00"

declare i32 @printf(i8*, ...) 
declare i32 @scanf(i8*, ...)
declare i32 @puts(i8*)

declare i8* @malloc(i32)
declare i32 @strlen(i8*)
declare i8* @strcpy(i8*, i8*)
declare i8* @strcat(i8*, i8*)
declare void @free(i8*)
declare void @exit(i32)



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

define i8* @readString() {
entry:  
        %max = call i8* @malloc(i32 256)

        %t1 = getelementptr [9 x i8], [9 x i8]* @str, i32 0, i32 0

        call i32 (i8*, ...) @scanf(i8* %t1, i8* %max)
        %len = call i32 @strlen(i8* %max)
        %lenPlus = add i32 %len, 1

        %mall = call i8* @malloc(i32 %lenPlus)
        %ret = call i8* @strcpy(i8* %mall, i8* %max)

        call void @free(i8* %max)
        ret i8* %mall       
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