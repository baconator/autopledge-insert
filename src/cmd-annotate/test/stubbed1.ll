; ModuleID = 'stubbed1.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: nounwind uwtable
define void @stub1() #0 {
  ret void
}

; Function Attrs: nounwind uwtable
define void @stub2() #0 {
  ret void
}

; Function Attrs: nounwind uwtable
define void @stub3() #0 {
  ret void
}

; Function Attrs: nounwind uwtable
define void @b() #0 {
  call void @stub3()
  ret void
}

; Function Attrs: nounwind uwtable
define void @a() #0 {
  call void @b()
  ret void
}

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i8**, align 8
  %i = alloca i32, align 4
  %i1 = alloca i32, align 4
  store i32 0, i32* %1
  store i32 %argc, i32* %2, align 4
  store i8** %argv, i8*** %3, align 8
  store i32 0, i32* %i, align 4
  store i32 0, i32* %i1, align 4
  br label %4

; <label>:4                                       ; preds = %20, %0
  %5 = load i32* %i1, align 4
  %6 = icmp slt i32 %5, 10000
  br i1 %6, label %7, label %23

; <label>:7                                       ; preds = %4
  %8 = load i32* %i1, align 4
  %9 = srem i32 %8, 2
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %12

; <label>:11                                      ; preds = %7
  call void @stub1()
  br label %19

; <label>:12                                      ; preds = %7
  %13 = load i32* %i1, align 4
  %14 = srem i32 %13, 3
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %17

; <label>:16                                      ; preds = %12
  call void @stub3()
  br label %18

; <label>:17                                      ; preds = %12
  call void @stub2()
  br label %18

; <label>:18                                      ; preds = %17, %16
  br label %19

; <label>:19                                      ; preds = %18, %11
  br label %20

; <label>:20                                      ; preds = %19
  %21 = load i32* %i1, align 4
  %22 = add nsw i32 %21, 1
  store i32 %22, i32* %i1, align 4
  br label %4

; <label>:23                                      ; preds = %4
  %24 = load i32* %i, align 4
  %25 = add nsw i32 %24, 1
  store i32 %25, i32* %i, align 4
  call void @a()
  store i32 0, i32* %i, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"Ubuntu clang version 3.6.2-1 (tags/RELEASE_362/final) (based on LLVM 3.6.2)"}
