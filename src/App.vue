<template>
  <div id="app">
    <el-container>
      <el-header>
        <Header></Header>
      </el-header>
      <el-container>
        <el-aside>
          <Aside></Aside>
        </el-aside>
        <el-main>Main</el-main>
      </el-container>
      <el-footer>Footer</el-footer>
    </el-container>
  </div>
</template>

<script>
import Header from './components/Header/Header'
import Footer from './components/Footer/Footer'
import Aside from './components/Aside/Aside'
export default {
  name: 'App',
  components: {
    Header,
    Footer,
    Aside
  }
}
</script>

<style>
  .el-header {
    padding: 0 0;
    background-color:#409EFF;
  }
  body {
    margin: 0 0;
  }
</style>
