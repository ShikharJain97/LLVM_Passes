; ModuleID = '/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Programs_Observing_C_Constructs/10022021_3.c'
source_filename = "/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Programs_Observing_C_Constructs/10022021_3.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [18 x i8] c" For loop work %d\00", align 1
@.str.1 = private unnamed_addr constant [20 x i8] c" while loop work %d\00", align 1
@.str.2 = private unnamed_addr constant [23 x i8] c" do-while loop work %d\00", align 1
@.str.3 = private unnamed_addr constant [9 x i8] c" goto %d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %start = alloca i32, align 4
  %end = alloca i32, align 4
  %jump1 = alloca i32, align 4
  %jump2 = alloca i32, align 4
  %jump3 = alloca i32, align 4
  %end_goto_flag = alloca i32, align 4
  %work = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 0, i32* %start, align 4
  store i32 10, i32* %end, align 4
  store i32 1, i32* %jump1, align 4
  store i32 2, i32* %jump2, align 4
  store i32 3, i32* %jump3, align 4
  store i32 0, i32* %end_goto_flag, align 4
  store i32 0, i32* %work, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %start, align 4
  %1 = load i32, i32* %end, align 4
  %cmp = icmp slt i32 %0, %1
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %2 = load i32, i32* %start, align 4
  %3 = load i32, i32* %work, align 4
  %add = add nsw i32 %3, %2
  store i32 %add, i32* %work, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %4 = load i32, i32* %start, align 4
  %5 = load i32, i32* %jump1, align 4
  %add1 = add nsw i32 %4, %5
  %6 = load i32, i32* %start, align 4
  %add2 = add nsw i32 %6, %add1
  store i32 %add2, i32* %start, align 4
  br label %for.cond, !llvm.loop !2

for.end:                                          ; preds = %for.cond
  %7 = load i32, i32* %work, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str, i64 0, i64 0), i32 %7)
  store i32 0, i32* %work, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %for.end
  %8 = load i32, i32* %start, align 4
  %9 = load i32, i32* %end, align 4
  %cmp3 = icmp slt i32 %8, %9
  br i1 %cmp3, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %10 = load i32, i32* %jump2, align 4
  %11 = load i32, i32* %work, align 4
  %sub = sub nsw i32 %11, %10
  store i32 %sub, i32* %work, align 4
  br label %while.cond, !llvm.loop !4

while.end:                                        ; preds = %while.cond
  %12 = load i32, i32* %work, align 4
  %call4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.1, i64 0, i64 0), i32 %12)
  store i32 0, i32* %work, align 4
  br label %do.body

do.body:                                          ; preds = %do.cond, %while.end
  %13 = load i32, i32* %jump3, align 4
  %14 = load i32, i32* %work, align 4
  %mul = mul nsw i32 %14, %13
  store i32 %mul, i32* %work, align 4
  br label %do.cond

do.cond:                                          ; preds = %do.body
  %15 = load i32, i32* %start, align 4
  %16 = load i32, i32* %end, align 4
  %cmp5 = icmp slt i32 %15, %16
  br i1 %cmp5, label %do.body, label %do.end, !llvm.loop !5

do.end:                                           ; preds = %do.cond
  %17 = load i32, i32* %work, align 4
  %call6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.2, i64 0, i64 0), i32 %17)
  br label %l1

l1:                                               ; preds = %if.end, %do.end
  %18 = load i32, i32* %start, align 4
  %19 = load i32, i32* %end, align 4
  %cmp7 = icmp slt i32 %18, %19
  br i1 %cmp7, label %if.then, label %if.else

if.then:                                          ; preds = %l1
  %20 = load i32, i32* %start, align 4
  %call8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.3, i64 0, i64 0), i32 %20)
  %21 = load i32, i32* %start, align 4
  %add9 = add nsw i32 %21, 2
  store i32 %add9, i32* %start, align 4
  br label %if.end

if.else:                                          ; preds = %l1
  br label %l2

if.end:                                           ; preds = %if.then
  br label %l1

l2:                                               ; preds = %if.else
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
!4 = distinct !{!4, !3}
!5 = distinct !{!5, !3}
