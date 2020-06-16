#include <stdio.h>
#include <stdlib.h>
#include <linux/kvm.h>
#include <sys/ioctl.h>
#include <err.h>
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
  int kvm_fd, vm_fd, vcpu_fd;
  struct kvm_sregs sregs;
  struct kvm_regs regs;
  int ret;
  kvm_fd = open("/dev/kvm", O_RDWR | O_CLOEXEC);
  if(kvm_fd == -1)
  {
     printf("Error!");
     exit(1);
  }

  ret = ioctl(kvm_fd, KVM_GET_API_VERSION, NULL);
  printf("KVM_API_VERSION = %d\n", ret);

  vm_fd = ioctl(kvm_fd, KVM_CREATE_VM, NULL);
  vcpu_fd = ioctl(vm_fd, KVM_CREATE_VCPU, NULL);
  ret = ioctl(vcpu_fd, KVM_GET_REGS, &regs);
  ret = ioctl(vcpu_fd, KVM_GET_SREGS, &sregs);
/*
 Print RAX, RIP, RFLAGS (general registers)
struct kvm_regs {
    __u64 rax, rbx, rcx, rdx;
    __u64 rsi, rdi, rsp, rbp;
    __u64 r8,  r9,  r10, r11;
    __u64 r12, r13, r14, r15;
    __u64 rip, rflags;
};
- Print CS.BASE (segment register)
struct kvm_sregs {
    struct kvm_segment cs, ds, es, fs, gs, ss;
    struct kvm_segment tr, ldt;
    struct kvm_dtable gdt, idt;
    __u64 cr0, cr2, cr3, cr4, cr8;
    __u64 efer;
    __u64 apic_base;
    __u64 interrupt_bitmap[(KVM_NR_INTERRUPTS + 63) / 64];
};
*/
  printf("RAX = %llu, RIP = %llu, RFLAGS = %llu\n" , regs.rax, regs.rip, regs.rflags);
  printf("SEGMENT REGISTER CS.BASE = %llu\n", sregs.cs.base);
  return 0;
}
