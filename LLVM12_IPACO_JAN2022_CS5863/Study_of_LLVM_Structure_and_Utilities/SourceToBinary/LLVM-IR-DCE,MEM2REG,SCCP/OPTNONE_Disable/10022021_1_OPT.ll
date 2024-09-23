; ModuleID = '/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Programs_Observing_C_Constructs/10022021_1.c'
source_filename = "/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Programs_Observing_C_Constructs/10022021_1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [21 x i8] c"a is %c and c is %d \00", align 1
@.str.1 = private unnamed_addr constant [21 x i8] c"a is not %c c is %d \00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"oops\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %aa = alloca i32, align 4
  %bb = alloca i32, align 4
  %cc = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 10, i32* %aa, align 4
  store i32 20, i32* %bb, align 4
  %0 = load i32, i32* %aa, align 4
  %1 = load i32, i32* %bb, align 4
  %cmp = icmp sgt i32 %0, %1
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %aa, align 4
  %3 = load i32, i32* %bb, align 4
  %mul = mul nsw i32 %2, %3
  %add = add nsw i32 %mul, 100
  store i32 %add, i32* %cc, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %4 = load i32, i32* %aa, align 4
  %5 = load i32, i32* %bb, align 4
  %sub = sub nsw i32 %4, %5
  store i32 %sub, i32* %cc, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %6 = load i32, i32* %aa, align 4
  %add1 = add nsw i32 %6, 75
  %rem = srem i32 %add1, 26
  %conv = trunc i32 %rem to i8
  %conv2 = sext i8 %conv to i32
  store i32 %conv2, i32* %aa, align 4
  %7 = load i32, i32* %aa, align 4
  switch i32 %7, label %sw.default [
    i32 75, label %sw.bb
    i32 65, label %sw.bb3
  ]

sw.bb:                                            ; preds = %if.end
  %8 = load i32, i32* %aa, align 4
  %9 = load i32, i32* %cc, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str, i64 0, i64 0), i32 %8, i32 %9)
  br label %sw.bb3

sw.bb3:                                           ; preds = %if.end, %sw.bb
  %10 = load i32, i32* %aa, align 4
  %11 = load i32, i32* %cc, align 4
  %call4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.1, i64 0, i64 0), i32 %10, i32 %11)
  br label %sw.default

sw.default:                                       ; preds = %if.end, %sw.bb3
  %call5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0))
  br label %sw.epilog

sw.epilog:                                        ; preds = %sw.default
  %12 = load i32, i32* %retval, align 4
  ret i32 %12
}

declare dso_local i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"}
