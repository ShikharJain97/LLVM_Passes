; ModuleID = '/home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/LLVM-IR-DCE,MEM2REG,SCCP/mem2Reg_sccp/10022021_4_sccp.bc'
source_filename = "/home/shikharj/CS5863_Program_Analysis_work/Assign_1/Programs_Observing_C_Constructs/10022021_4.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Dummy_struct = type { i32 }

@__const.main.St_ar = private unnamed_addr constant [5 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5], align 16
@.str = private unnamed_addr constant [10 x i8] c" %d %d %d\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"%d \00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  %St_ar = alloca [5 x i32], align 16
  %ob1 = alloca %struct.Dummy_struct, align 4
  %0 = bitcast [5 x i32]* %St_ar to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %0, i8* align 16 bitcast ([5 x i32]* @__const.main.St_ar to i8*), i64 20, i1 false)
  %call = call noalias i8* @malloc(i64 20) #4
  %1 = bitcast i8* %call to i32*
  %arrayidx = getelementptr inbounds i32, i32* %1, i64 0
  store i32 10, i32* %arrayidx, align 4
  %arrayidx1 = getelementptr inbounds i32, i32* %1, i64 1
  store i32 20, i32* %arrayidx1, align 4
  %arrayidx2 = getelementptr inbounds i32, i32* %1, i64 2
  store i32 30, i32* %arrayidx2, align 4
  %arrayidx3 = getelementptr inbounds i32, i32* %1, i64 3
  store i32 40, i32* %arrayidx3, align 4
  %arrayidx4 = getelementptr inbounds i32, i32* %1, i64 4
  store i32 50, i32* %arrayidx4, align 4
  %call5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i64 0, i64 0), i32 100, i32 100, i32 100)
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i.0, 5
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %idxprom = sext i32 %i.0 to i64
  %arrayidx6 = getelementptr inbounds [5 x i32], [5 x i32]* %St_ar, i64 0, i64 %idxprom
  %2 = load i32, i32* %arrayidx6, align 4
  %idxprom7 = sext i32 %i.0 to i64
  %arrayidx8 = getelementptr inbounds i32, i32* %1, i64 %idxprom7
  %3 = load i32, i32* %arrayidx8, align 4
  %add = add nsw i32 %2, %3
  %call9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0), i32 %add)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond, !llvm.loop !2

for.end:                                          ; preds = %for.cond
  %x = getelementptr inbounds %struct.Dummy_struct, %struct.Dummy_struct* %ob1, i32 0, i32 0
  store i32 1000, i32* %x, align 4
  %x10 = getelementptr inbounds %struct.Dummy_struct, %struct.Dummy_struct* %ob1, i32 0, i32 0
  %4 = load i32, i32* %x10, align 4
  %call11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i64 0, i64 0), i32 %4)
  ret i32 0
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* noalias nocapture writeonly, i8* noalias nocapture readonly, i64, i1 immarg) #1

; Function Attrs: nounwind
declare dso_local noalias i8* @malloc(i64) #2

declare dso_local i32 @printf(i8*, ...) #3

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { nounwind "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 12.0.1 (https://github.com/llvm/llvm-project.git fed41342a82f5a3a9201819a82bf7a48313e296b)"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.mustprogress"}
