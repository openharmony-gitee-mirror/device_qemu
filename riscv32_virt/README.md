### Qemu RISC-V virt HOWTO

#### 1. Brief introduction
`riscv32_virt/` subdirectory contains part of the OpenHarmony LiteOS demonstration support for Qemu risc-v virt Platform,
here called *virt*.
RISC-V Virtual platform is a `qemu-system-riscv32` machine target that provides emulation
for a generic, riscv-based board.

Introduced functionality adds support for RISC-V (1 CPU with security extensions), 128MB memory virtual platform.

Note: System memory size is hard-coded to 128MB.

#### 2. Setting up environment

[Setting up a development environment](https://gitee.com/openharmony/docs/blob/master/en/device-dev/quick-start/environment-setup.md)

[Compiler install: gcc_riscv32](https://gitee.com/openharmony/docs/blob/master/en/device-dev/quick-start/setting-up-the-environment.md), 
Note: [Downloadable directly](https://repo.huaweicloud.com/harmonyos/compiler/gcc_riscv32/7.3.0/linux/gcc_riscv32-linux-7.3.0.tar.gz)

#### 3. Code acquisition

[Code acquisition](https://gitee.com/openharmony/docs/blob/master/en/device-dev/get-code/source-code-acquisition.md)

Note: One can use `repo` to fetch code in a straightforward manner.

#### 4. Building from sources

```
cd device/qemu/riscv32_virt
make clean;make -j16
```

This will build `OHOS_Image` for Qemu ARM virt machine.


After build is finished, the resulting image can be found in:
```
out/OHOS_Image
```
#### 5. Running image in Qemu

a) If not installed, please install `qemu-system-riscv32`
For details, please refer to the HOWTO: [Qemu installation](https://gitee.com/openharmony/device_qemu/blob/master/README.md)

b) Run

(1) qemu version < 5.0.0

```
cd device/qemu/riscv32_virt
qemu-system-riscv32 -machine virt -m 128M -kernel out/OHOS_Image -nographic -append "root=dev/vda or console=ttyS0"
```

(2). qemu version >= 5.0.0 

```
cd device/qemu/riscv32_virt
./qemu-system-riscv32 out/OHOS_Image
or
qemu-system-riscv32 -machine virt -m 128M -bios none -kernel out/OHOS_Image -nographic -append "root=dev/vda or console=ttyS0"
```