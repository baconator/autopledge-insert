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
  store i32 0, i32* %1
  store i32 %argc, i32* %2, align 4
  store i8** %argv, i8*** %3, align 8
  store i32 0, i32* %i, align 4
  call void @stub1()
  call void @stub2()
  %4 = load i32* %i, align 4
  %5 = add nsw i32 %4, 1
  store i32 %5, i32* %i, align 4
  call void @a()
  store i32 0, i32* %i, align 4
  ret i32 0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"Ubuntu clang version 3.6.2-1 (tags/RELEASE_362/final) (based on LLVM 3.6.2)"}
