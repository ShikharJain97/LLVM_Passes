; ModuleID = '/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Complex_c_Programs/Multi_func_call.c'
source_filename = "/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Complex_c_Programs/Multi_func_call.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [3 x i8] c"%f\00", align 1
@.str.1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%c\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func1(i32 %a, i32 %b) #0 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  store i32 %b, i32* %b.addr, align 4
  %0 = load i32, i32* %a.addr, align 4
  %1 = load i32, i32* %b.addr, align 4
  %mul = mul nsw i32 %0, %1
  %2 = load i32, i32* %b.addr, align 4
  %sub = sub nsw i32 %2, 10
  %div = sdiv i32 %sub, 71
  %add = add nsw i32 %mul, %div
  store i32 %add, i32* %x, align 4
  %3 = load i32, i32* %x, align 4
  ret i32 %3
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local double @func2(i32* %a, i32* %b) #0 {
entry:
  %a.addr = alloca i32*, align 8
  %b.addr = alloca i32*, align 8
  store i32* %a, i32** %a.addr, align 8
  store i32* %b, i32** %b.addr, align 8
  %0 = load i32*, i32** %a.addr, align 8
  %1 = load i32, i32* %0, align 4
  %2 = load i32*, i32** %b.addr, align 8
  %3 = load i32, i32* %2, align 4
  %call = call i32 @func1(i32 %1, i32 %3)
  %4 = load i32*, i32** %b.addr, align 8
  %5 = load i32, i32* %4, align 4
  %6 = load i32*, i32** %a.addr, align 8
  %7 = load i32, i32* %6, align 4
  %sub = sub nsw i32 %5, %7
  %add = add nsw i32 %call, %sub
  %8 = load i32*, i32** %a.addr, align 8
  store i32 %add, i32* %8, align 4
  %9 = load i32*, i32** %a.addr, align 8
  %10 = load i32, i32* %9, align 4
  %conv = sitofp i32 %10 to double
  %mul = fmul double %conv, 5.660000e+00
  ret double %mul
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @func3(i32 %a) #0 {
entry:
  %a.addr = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  %0 = load i32, i32* %a.addr, align 4
  %add = add nsw i32 %0, 10
  %mul = mul nsw i32 %add, 77
  %rem = srem i32 %mul, 26
  %add1 = add nsw i32 65, %rem
  ret i32 %add1
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 20, i32* %a, align 4
  store i32 300, i32* %b, align 4
  %call = call double @func2(i32* %a, i32* %b)
  %call1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), double %call)
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.1, i64 0, i64 0))
  %0 = load i32, i32* %a, align 4
  %call3 = call i32 @func3(i32 %0)
  %call4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i64 0, i64 0), i32 %call3)
  ret i32 0
}

declare dso_local i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"}
