<template>
  <div class="aside">
    <el-menu
      default-active="2"
      class="el-menu-vertical-demo"
      background-color="#545c64"
      text-color="#fff"
      active-text-color="#67C23A"
    >
      <el-menu-item index="1">
        <span>
          <i class="el-icon-monitor"></i> 环境
        </span>
      </el-menu-item>
      <el-menu-item index="2">
        <span>
          <i class="el-icon-s-opportunity"></i> 问题
        </span>
      </el-menu-item>
      <el-menu-item index="3">
        <span>
          <i class="el-icon-collection-tag"></i> 分类
        </span>
      </el-menu-item>
      <el-menu-item index="4">
        <span>
          <i class="el-icon-data-line"></i> 状态
        </span>
      </el-menu-item>
      <el-menu-item index="5">
        <span>
          <i class="el-icon-s-platform"></i> 排名
        </span>
      </el-menu-item>
      <el-menu-item index="6">
        <span>
          <i class="el-icon-wind-power"></i> 竞赛
        </span>
      </el-menu-item>
    </el-menu>
  </div>
</template>

<script>
export default {
  data() {
    return {};
  }
};
</script>

<style scoped>
  .aside {
    position: absolute;
    top: 60px;
    bottom: 0px;
    width: 300px;
    background-color: #545c64;
  }
</style>
