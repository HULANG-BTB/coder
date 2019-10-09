<template>
  <el-container v-loading="loading">
    <el-header :style="{height: 'initial'}">
      <h2>{{ problemInfo.pid + ' : ' +problemInfo.title }}</h2>
      <h5>时间: {{ problemInfo.time }} s 内存: {{ problemInfo.memory }} MB</h5>
    </el-header>
    <el-main>
      <h3>题目描述</h3>
      <p v-html="problemInfo.description"></p>
      <h3>输入格式</h3>
      <p v-html="problemInfo.input ? problemInfo.input : '无'"></p>
      <h3>输出格式</h3>
      <p v-html="problemInfo.output ? problemInfo.output : '无'"></p>
      <h3>样例输入</h3>
      <el-input
        type="textarea"
        :autosize="{ minRows: 4, maxRows: 7}"
        v-model="problemInfo.sample_input">
      </el-input>
      <h3>样例输出</h3>
      <el-input
        type="textarea"
        :autosize="{ minRows: 4, maxRows: 7}"
        v-model="problemInfo.sample_output">
      </el-input>
      <h3 v-if="problemInfo.hint">提示信息</h3>
      <p v-html="problemInfo.hint" v-if="problemInfo.hint"></p>
      <h3 v-if="problemInfo.source">题目来源</h3>
      <p v-html="problemInfo.source" v-if="problemInfo.source"></p>
    </el-main>
    <el-footer :style="{height: 'initial'}">
      <el-button type="primary" @click.prevent="redirect('submit')">提交代码</el-button>
      <el-button type="primary" @click.prevent="redirect('status')">提交状态</el-button>
    </el-footer>
  </el-container>
</template>

<script>
import {
  mapActions,
  mapState
} from 'vuex'
export default {
  data () {
    return {
      id: this.$route.query.id
    }
  },
  computed: {
    ...mapState(['problemInfo']),
    loading () {
      return this.problemInfo.title === undefined
    }
  },
  methods: {
    ...mapActions(['getProblemInfo', 'setProblemInfo']),
    redirect (direct) {
      if (direct === 'submit') {
        this.$router.push({name: 'ProblemSubmit', query: {id: this.id}})
      } else if (direct === 'status') {
        this.$router.push({name: 'ProblemStatus', query: {id: this.id}})
      }
    }
  },
  mounted () {
    this.setProblemInfo({})
    this.getProblemInfo({id: this.id})
  }
}
</script>

<style scoped>
.el-header {
  text-align: center;
}
.el-main {
  box-shadow: 0 2px 4px rgba(0, 0, 0, .12), 0 0 6px rgba(0, 0, 0, .12);
  border-radius: 4px;
}
.el-footer {
  margin-top: 10px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, .12), 0 0 6px rgba(0, 0, 0, .12);
  border-radius: 4px;
  text-align: center;
  padding: 10px;
}
p {
  padding: 0 15px;
  border-radius: 4px;
  border-left: solid 1px #e6e6e6;
 }
</style>
