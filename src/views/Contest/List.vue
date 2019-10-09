<template>
  <el-container>
    <el-header :style="{height: 'initial'}">
      <el-row style="text-align: center;">
        <el-row>
          <h1>竞赛列表</h1>
          <el-input placeholder="请输入关键字" v-model="keyword" class="input-with-select">
            <el-button slot="append" icon="el-icon-search" @click="search"></el-button>
          </el-input>
        </el-row>
      </el-row>
    </el-header>
    <el-main>
      <el-table
        :data="tableData"
        style="width: 100%"
        border
        fit
      >
        <el-table-column
          label="竞赛编号"
          width="100">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.cid }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="标题">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.title }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="开始时间"
          width="180">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ timestampToTime(scope.row.start_time) }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="结束时间"
          width="180">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ timestampToTime(scope.row.end_time) }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="私有"
          width="140">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.private }}</span>
          </template>
        </el-table-column>
        <el-table-column
          label="状态"
          width="140">
          <template slot-scope="scope">
            <span style="margin-left: 10px" v-html="formateStatus(scope.row)"></span>
          </template>
        </el-table-column>
        <el-table-column
          label="创建者"
          width="140">
          <template slot-scope="scope">
            <span style="margin-left: 10px">{{ scope.row.uid }}</span>
          </template>
        </el-table-column>
      </el-table>
    </el-main>
    <el-footer>
      <el-pagination
        @size-change="handleSizeChange"
        @current-change="handlePageChange"
        :current-page="page"
        :page-sizes="[10, 20, 50, 100]"
        :page-size="limit"
        layout="total, sizes, prev, pager, next, jumper"
        :total="total">
      </el-pagination>
    </el-footer>
  </el-container>
</template>

<script>
import {mapActions, mapState} from 'vuex'

export default {
  data () {
    return {
      page: parseInt(this.$route.query.page) || 1,
      limit: parseInt(this.$route.query.limit) || 10,
      keyword: this.$route.query.keyword || ''
    }
  },
  computed: {
    tableData () {
      return this.contestList.data
    },
    ...mapState(['contestList']),
    total () {
      return this.contestList.total
    }
  },
  mounted () {
    const query = this.buildQuery()
    this.getContestList(query)
  },
  methods: {
    ...mapActions(['getContestList']),
    handlePageChange (data) {
      this.page = data
      const query = this.buildQuery()
      this.$router.push({name: 'ContestList', query: query})
      this.getContestList(query)
    },
    handleSizeChange (data) {
      this.limit = data
      const query = this.buildQuery()
      this.$router.push({name: 'ContestList', query: query})
      this.getContestList(query)
    },
    search () {
      if (this.type !== '') {
        this.page = 1
        const query = this.buildQuery()
        this.$router.push({name: 'ContestList', query: query})
        this.getContestList(query)
      }
    },
    buildQuery () {
      return {
        page: this.page,
        limit: this.limit,
        type: this.type,
        keyword: this.keyword
      }
    },
    timestampToTime (data) {
      const date = new Date(data * 1000)
      const Y = date.getFullYear() + '-'
      const M = (date.getMonth() + 1 < 10 ? '0' + (date.getMonth() + 1) : date.getMonth() + 1) + '-'
      const D = (date.getDate() < 10 ? '0' + date.getDate() : date.getDate()) + ' '
      const h = (date.getHours() < 10 ? '0' + date.getHours() : date.getHours()) + ':'
      const m = (date.getMinutes() < 10 ? '0' + date.getMinutes() : date.getMinutes()) + ':'
      const s = (date.getSeconds() < 10 ? '0' + date.getSeconds() : date.getSeconds())
      return Y + M + D + h + m + s
    },
    formateStatus (data) {
      const now = new Date().valueOf() / 1000
      if (now >= data.start_time && now < data.end_time) return '<span style="color:green">运行中</span>'
      else if (now > data.end_time) return '<span style="color:red">已结束</span>'
      else return '<span style="color:red">未开始</span>'
    }
  }
}
</script>

<style scoped>
.el-select {
  width: 150px;
}
</style>
