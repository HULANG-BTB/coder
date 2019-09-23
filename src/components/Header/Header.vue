<template>
  <div class="header">
    <div class="logo">
      <div class="img"></div>
      <div class="title">Lazy OJ</div>
    </div>
    <div class="nav">
      <el-menu class="el-menu-demo" mode="horizontal" background-color="#409EFF" text-color="#fff">
        <el-submenu index="1">
          <template slot="title">
            <i class="el-icon-s-promotion"></i>
            <span>消息</span>
          </template>
          <el-menu-item index="1-1">没有新消息</el-menu-item>
        </el-submenu>
        <el-menu-item index="2">
          <a>登录</a>
        </el-menu-item>
        <el-menu-item index="3">
          <a>注册</a>
        </el-menu-item>
      </el-menu>
    </div>
  </div>
</template>

<script>
export default {
  data () {
    return {}
  }
}
</script>

<style scoped>
.header > .logo {
  padding-top: 10px;
  padding-left: 10px;
  float: left;
}
.header > .logo .img {
  width: 30px;
  height: 30px;
  float: left;
}
.header > .logo .title {
  font-family: "MV Boli";
  font-size: 24px;
  float: left;
}
.header > .nav {
  float: right;
}
.header i {
  color: black;
}
</style>
