vlib work
vlib activehdl

vlib activehdl/xilinx_vip
vlib activehdl/xil_defaultlib
vlib activehdl/xpm
vlib activehdl/axi_infrastructure_v1_1_0
vlib activehdl/axi_vip_v1_1_5
vlib activehdl/processing_system7_vip_v1_0_7
vlib activehdl/blk_mem_gen_v8_4_3
vlib activehdl/generic_baseblocks_v2_1_0
vlib activehdl/axi_register_slice_v2_1_19
vlib activehdl/fifo_generator_v13_2_4
vlib activehdl/axi_data_fifo_v2_1_18
vlib activehdl/axi_crossbar_v2_1_20
vlib activehdl/lib_cdc_v1_0_2
vlib activehdl/proc_sys_reset_v5_0_13
vlib activehdl/axi_protocol_converter_v2_1_19

vmap xilinx_vip activehdl/xilinx_vip
vmap xil_defaultlib activehdl/xil_defaultlib
vmap xpm activehdl/xpm
vmap axi_infrastructure_v1_1_0 activehdl/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_5 activehdl/axi_vip_v1_1_5
vmap processing_system7_vip_v1_0_7 activehdl/processing_system7_vip_v1_0_7
vmap blk_mem_gen_v8_4_3 activehdl/blk_mem_gen_v8_4_3
vmap generic_baseblocks_v2_1_0 activehdl/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_19 activehdl/axi_register_slice_v2_1_19
vmap fifo_generator_v13_2_4 activehdl/fifo_generator_v13_2_4
vmap axi_data_fifo_v2_1_18 activehdl/axi_data_fifo_v2_1_18
vmap axi_crossbar_v2_1_20 activehdl/axi_crossbar_v2_1_20
vmap lib_cdc_v1_0_2 activehdl/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_13 activehdl/proc_sys_reset_v5_0_13
vmap axi_protocol_converter_v2_1_19 activehdl/axi_protocol_converter_v2_1_19

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2019.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xil_defaultlib  -sv2k12 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2019.1/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ipshared/d6e9/src/debounce.vhd" \
"../../../bd/design_1/ipshared/d6e9/hdl/kybd_slv_v1_0_S00_AXI.vhd" \
"../../../bd/design_1/ipshared/d6e9/src/ps2_keyboard.vhd" \
"../../../bd/design_1/ipshared/d6e9/hdl/kybd_slv_v1_0.vhd" \
"../../../bd/design_1/ip/design_1_kybd_slv_0_1/sim/design_1_kybd_slv_0_1.vhd" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_5  -sv2k12 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/d4a8/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_7  -sv2k12 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \

vlog -work blk_mem_gen_v8_4_3  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_slv_0_0/src/blk_mem_gen_0_1/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_slv_0_0/src/blk_mem_gen_0_1/sim/blk_mem_gen_0.v" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ipshared/bc0d/src/ascii_writer.vhd" \
"../../../bd/design_1/ipshared/bc0d/src/char8x12_lookup_table.vhd" \
"../../../bd/design_1/ipshared/bc0d/hdl/slv_v1_0_S00_AXI.vhd" \
"../../../bd/design_1/ipshared/bc0d/src/vga_sync.vhd" \
"../../../bd/design_1/ipshared/bc0d/hdl/slv_v1_0.vhd" \
"../../../bd/design_1/ip/design_1_slv_0_0/sim/design_1_slv_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_19  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/4d88/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_4  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/1f5a/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_4 -93 \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/1f5a/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_4  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/1f5a/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_18  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/5b9c/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_20  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ace7/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0/sim/design_1_rst_ps7_0_50M_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0_clk_wiz.v" \
"../../../bd/design_1/ip/design_1_clk_wiz_0_0/design_1_clk_wiz_0_0.v" \

vlog -work axi_protocol_converter_v2_1_19  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c83a/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/8c62/hdl" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ipshared/c923" "+incdir+../../../../Project6_test.srcs/sources_1/bd/design_1/ip/design_1_processing_system7_0_0" "+incdir+C:/Xilinx/Vivado/2019.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

