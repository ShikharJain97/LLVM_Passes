; ModuleID = '/home/shikharj/Simple_c_Progs/array_right_circular_shift.c'
source_filename = "/home/shikharj/Simple_c_Progs/array_right_circular_shift.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@__const.main.arr = private unnamed_addr constant [5 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5], align 16
@.str = private unnamed_addr constant [36 x i8] c" Array elements are %d %d %d %d %d \00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %arr = alloca [5 x i32], align 16
  %i = alloca i32, align 4
  %temp = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  %0 = bitcast [5 x i32]* %arr to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %0, i8* align 16 bitcast ([5 x i32]* @__const.main.arr to i8*), i64 20, i1 false)
  %arrayidx = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 4
  %1 = load i32, i32* %arrayidx, align 16
  store i32 %1, i32* %temp, align 4
  store i32 3, i32* %i, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i32, i32* %i, align 4
  %cmp = icmp sge i32 %2, 0
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %3 = load i32, i32* %i, align 4
  %idxprom = sext i32 %3 to i64
  %arrayidx1 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 %idxprom
  %4 = load i32, i32* %arrayidx1, align 4
  %5 = load i32, i32* %i, align 4
  %add = add nsw i32 %5, 1
  %idxprom2 = sext i32 %add to i64
  %arrayidx3 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 %idxprom2
  store i32 %4, i32* %arrayidx3, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %6 = load i32, i32* %i, align 4
  %dec = add nsw i32 %6, -1
  store i32 %dec, i32* %i, align 4
  br label %for.cond, !llvm.loop !2

for.end:                                          ; preds = %for.cond
  %7 = load i32, i32* %temp, align 4
  %arrayidx4 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 0
  store i32 %7, i32* %arrayidx4, align 16
  %arrayidx5 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 0
  %8 = load i32, i32* %arrayidx5, align 16
  %arrayidx6 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 1
  %9 = load i32, i32* %arrayidx6, align 4
  %arrayidx7 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 2
  %10 = load i32, i32* %arrayidx7, align 8
  %arrayidx8 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 3
  %11 = load i32, i32* %arrayidx8, align 4
  %arrayidx9 = getelementptr inbounds [5 x i32], [5 x i32]* %arr, i64 0, i64 4
  %12 = load i32, i32* %arrayidx9, align 16
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str, i64 0, i64 0), i32 %8, i32 %9, i32 %10, i32 %11, i32 %12)
  %13 = load i32, i32* %retval, align 4
  ret i32 %13
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #1

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind optnone uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
