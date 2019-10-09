<template>
  <el-menu
    :default-active="activeIndex"
    class="el-menu-vertical-demo"
    text-color="#000"
    active-text-color="#67C23A"
  >
    <el-menu-item index="Environment" @click="redirect('/Environment')">
        <span>
          <i class="el-icon-monitor"></i> 环境
        </span>
    </el-menu-item>
    <el-menu-item index="Problem" @click="redirect('/Problem')">
        <span>
          <i class="el-icon-s-opportunity"></i> 问题
        </span>
    </el-menu-item>
    <el-menu-item index="Category" @click="redirect('/Category')">
        <span>
          <i class="el-icon-collection-tag"></i> 分类
        </span>
    </el-menu-item>
    <el-menu-item index="Status" @click="redirect('/Status')">
        <span>
          <i class="el-icon-data-line"></i> 状态
        </span>
    </el-menu-item>
    <el-menu-item index="Rank" @click="redirect('/Rank')">
        <span>
          <i class="el-icon-s-platform"></i> 排名
        </span>
    </el-menu-item>
    <el-menu-item index="Contest" @click="redirect('/Contest')">
        <span>
          <i class="el-icon-wind-power"></i> 竞赛
        </span>
    </el-menu-item>
  </el-menu>
</template>

<script>
export default {
  data () {
    return {
    }
  },
  methods: {
    redirect (path) {
      if (this.$route.path !== path) this.$router.push(path)
    }
  },
  created: function () {
  },
  computed: {
    activeIndex () {
      return this.$route.path.substring(1, this.$route.path.indexOf('/', 1) === -1 ? this.$route.path.length : this.$route.path.indexOf('/', 1))
    }
  }
}
</script>

<style>
.el-aside {
  border-right: solid 1px #e6e6e6;
}
</style>
